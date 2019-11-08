#include "map.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
using namespace std;
template<typename K, typename V>
  class BstMap: public Map <K, V>{
 private:
  //a class for each node
  class Node {
  public:
    K key;
    V value;
    Node * left;
    Node * right;
  Node(K a, V b, Node * c, Node * d): key(a), value(b), left(c), right(d) {}
    ~Node() {}
  };
  Node * root;

 public:
 BstMap():root(NULL) {}
  //copy assignment
 BstMap(const BstMap & rhs): root(NULL) {
    deepcopy(rhs.root);
  }
  BstMap & operator=(const BstMap & rhs) {
    destroy(root);
    root = NULL;
    deepcopy(rhs.root);
    return *this;
  }
  void print(const Node * curr) {
    if(curr != NULL) {
      cout << "key: " << curr->key << "value: " << curr->value << endl;
      print(curr->left);
      print(curr->right);
    }
  }

 virtual ~BstMap(){
    destroy(root);
    root = NULL;
  }
  void deepcopy(const Node * curr) {
    if(curr != NULL) {
      add(curr->key, curr->value);
      deepcopy(curr->left);
      deepcopy(curr->right);
    }
  }
 Node * getroot() const {
   return root;
 }
 Node * getroot() {
   return root;
 }
  void destroy(Node * curr) {
    if (curr != NULL) {
      destroy(curr->left);
      destroy(curr->right);
      delete curr;
    }
  }
  
  virtual void add(const K & key, const V & value) {
    Node ** curr = &root;
    while(*curr != NULL) {
      if( key < (*curr)->key ) {
	curr = &(*curr)->left;
      }
      else if( key > (*curr)->key ) {
	curr = &(*curr)->right;
      }
      else {
	(*curr)->value = value;
	return;
      }
    }
    *curr = new Node(key, value, NULL, NULL); 
  }
  



  
  virtual const V & lookup(const K& key) const throw (invalid_argument) {
    try {
      const Node * curr = root;
      while(curr != NULL) {
	if(key < curr->key) {
	  curr = curr->left;
	}
	else if(key > curr->key) {
	  curr = curr->right;
	}
	else {
	  return curr->value;
	}
      }
      throw invalid_argument("no this key");
    }
    catch (const invalid_argument & e) {
      throw;
    }
  }

  virtual void remove(const K& key) {
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
    while( (final2->left != NULL) || (final2->right != NULL) ) {
      final1 = final2;
      if(final2->right != NULL) {
	final2 = final2->right;
      }
      else {
	final2 = final2->left;
      }
    }
    // free eage between final1 and final2
    if(final1->left == final2) {
      final1->left = NULL;
    }
    else {
      final1->right = NULL;
    }
    final2->left = (*curr)->left;
    final2->right = (*curr)->right;
    delete *curr;
    *curr = final2;
  }
  
};
