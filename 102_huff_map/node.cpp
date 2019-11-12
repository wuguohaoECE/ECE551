
#include "node.h"
void Node::buildMap(BitString b, std::map<unsigned,BitString> & theMap) {
  //WRITE ME!
  if(left != NULL) {
    left->buildMap(b.plusZero(), theMap);
  }
  if(right != NULL) {
    right->buildMap(b.plusOne(), theMap);
  }
  if(sym != 999) {
    theMap[sym]= b;
  }
}

