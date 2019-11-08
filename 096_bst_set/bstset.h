#include "set.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

using namespace std;
template<typename T>
  class BstSet: public Set <T>{
 private:
  //a class for each node
  class Node {
  public:
    T key;
    Node * left;
    Node * right;
  Node(T a, Node * c, Node * d): key(a), left(c), right(d) {}
    ~Node() {}
  };
  Node * root;
  
 public:
 BstSet():root(NULL) {}
  //copy assignment
 BstSet(const BstSet & rhs): root(NULL) {
    deepcopy(rhs.root);
  }
  
  BstSet & operator=(const BstSet & rhs) {
    destroy(root);
    root = NULL;
    deepcopy(rhs.root);
    return *this;
  }
  
 virtual ~BstSet(){
    destroy(root);
    root = NULL;
  }
 
  void deepcopy(const Node * curr) {
    if(curr != NULL) {
      add(curr->key);
      deepcopy(curr->left);
      deepcopy(curr->right);
    }
  }

  void destroy(Node * curr) {
    if (curr != NULL) {
      destroy(curr->left);
      destroy(curr->right);
      delete curr;
    }
  }

  virtual void add(const T & key) {
    Node ** curr = &root;
    while(*curr != NULL) {
      if( key < (*curr)->key ) {
	curr = &(*curr)->left;
      }
      else if( key > (*curr)->key ) {
	curr = &(*curr)->right;
      }
      else {
	return;
      }
    }
    *curr = new Node(key, NULL, NULL); 
  }

  virtual bool contains(const T& key) const {
    const Node * curr = root;
    while(curr != NULL) {
      if(key < curr->key) {
	curr = curr->left;
      }
      else if(key > curr->key) {
	curr = curr->right;
      }
      else {
	return true;
      }
    }
    return false;
  }

  virtual void remove(const T& key) {
    Node ** curr = &root;
    while(*curr != NULL) {
      if( key < (*curr)->key ) {
	curr = &(*curr)->left;
      }
      else if( key > (*curr)->key ) {
	curr = &(*curr)->right;
      }
      else {
        break;
      }
    }
    // key not exist
    if(*curr == NULL) {
      return;
    }
    if( (*curr)->left == NULL) {
      Node * temp = (*curr)->right;
      delete *curr;
      *curr = temp;
      return;
    }
    if( (*curr)->right == NULL) {
      Node * temp = (*curr)->left;
      delete *curr;
      *curr = temp;
      return;
    }
    //find the Node used to replace the deleted one
    //left once, and to the top right
    Node * final1 = *curr;
    Node * final2 = (*curr)->left;
    if(final2->right != NULL) {
      do {
	final1 = final2;
	final2 = final2->right;
      } while(final2->right != NULL);
      
      final1->right = final2->left;
      final2->left = (*curr)->left;
    }
    
    final2->right = (*curr)->right;
    delete *curr;
    *curr = final2;
  }
};
