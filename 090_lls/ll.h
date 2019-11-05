#ifndef _LL_H_
#define _LL_H_
#include <cstdlib>
#include <exception>
#include <assert.h>
#include <iostream>
//YOUR CODE GOES HERE
using namespace std;

template<typename T>
class LinkedList {
 private:
  class Node {
  public:
    T data;
    Node * next;
    Node * previous;
  Node() : next(NULL), previous(NULL){};
  Node(const T & a, Node * b, Node * c): data(a), next(b), previous(c) {};
  };
  Node * head;
  Node * tail;
  int size;
 public:
  //iterator 
  class iterator {
  private:
    Node * current;
  public:
  iterator() : current(NULL) {}
    explicit iterator(Node * c) :current(c) {}
    T & operator*() const {
      return current->data;
    }
    bool operator!=(const iterator & rhs) const {
      return current != rhs.current;
    }
  
    iterator & operator++() {
      current = current->next;
      return *this;
    }
  };
  
  class const_iterator {
  private:
    const Node * current;
  public:
  const_iterator() : current(NULL) {}
    explicit const_iterator(const Node * c) : current(c) {}
    const T & operator*() const {
      return current->data;
    }
    bool operator!=(const const_iterator & rhs) const {
      return current != rhs.current;
    }
  
    const const_iterator & operator++() {
      current = current->next;
      return *this;
    }
  };  
  iterator begin() { return iterator(head); }
  iterator end() { return iterator(NULL); }

  const_iterator begin() const { return const_iterator(head); }
  const_iterator end() const  { return const_iterator(NULL); }    
 LinkedList() : head(NULL), tail(NULL), size(0) {}
 LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size( rhs.getSize() ) {
    if(size > 0){
      LinkedList::const_iterator it = rhs.begin();
      head = new Node(*it, NULL, NULL);
      Node * tmp = head;
      ++it;
      while ( it != rhs.end() ) {
	tmp->next = new Node(*it,NULL,tmp);
	tmp = tmp->next;
	++it;
      }
      tail = tmp;
    }
  }
  LinkedList & operator=(LinkedList & rhs) {
    if (this != &rhs) {
      LinkedList tmp(rhs);
      while (head != NULL) {
	Node * temp = head->next;
	delete head;
	head = temp;
      }
      head = tmp.head;
      tail = tmp.tail;
      size = tmp.size;

      // when size = 0, the destroctor of tmp will not delete node.
      tmp.size = 0;
    }
    return *this;
  }
  ~LinkedList() {
    Node * rem1 = head;
    Node * rem2;
    for(int i = 0; i < size; i++) {
      rem2 = rem1->next;
      delete rem1;
      rem1 = rem2;
    }
    head = NULL;
    tail = NULL;
    size = 0;
  }
  void addFront(const T &item) {
    head = new Node(item, head, NULL);
    if (tail == NULL) {
      tail = head;
    }
    else {
      head->next->previous = head;
    }
    size++;
  }
  void addBack(const T &item) {
    tail = new Node(item, NULL, tail);
    if (head == NULL) {
      head = tail;
    }
    else {
      tail->previous->next = tail;
    }
    size++;
  }
  
  // const version of []
  const T & operator[](int index) const {
    try {
      if (index > size || index < 0) {
	throw exception();
      }
      Node * ans = head;
      for(int i = 0; i < index; i++){
	ans = ans->next;
      }
      return ans->data;
    }
    catch(exception & e) {
      cout << " is out of range\n" << e.what() << " is out of range\n";
      exit(EXIT_FAILURE);
    }
  }
  // non-const version of []
  T & operator[](int index) {
    try {
      if (index > size || index < 0) {
	throw exception();
      }
      Node * ans = head;
      for(int i = 0; i < index; i++){
	ans = ans->next;
      }
      return ans->data;
    }
    catch(exception & e) {
      cout << " is out of range\n" << e.what() << " is out of range\n";
      exit(EXIT_FAILURE);
    }
  }
  bool remove(const T &item) {
    Node ** current = &head;
    while(*current != NULL && (*current)->data != item) {
      current = &(*current)->next;
    }
    if( *current == NULL ) {
      return false;
    }
    if( (*current)->next != NULL ) {
      (*current)->next->previous = (*current)->previous;
    }
    Node * temp = (*current)->next;
    delete (*current);
    *current = temp;
    size--;
    return true;
  }
  int find(const T &item) {
    Node * tar = head;
    int ans = 0;
    while( (tar != NULL) && (tar->data != item) ) {
      tar = tar->next;
      ans++;
    }
    if ( tar != NULL ) {
      return ans;
    }
    return -1;
  }
  const int getSize() const {
    return size;
  }
};

#endif
