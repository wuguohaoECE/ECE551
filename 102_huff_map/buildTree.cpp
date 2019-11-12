#include "node.h"

Node *  buildTree(uint64_t * counts) {
  priority_queue_t pq;
  for(uint64_t i = 0; i < 257; i++) {
    if (counts[i] != 0) {
      pq.push(new Node(i,counts[i]));
    }
  }
  while(pq.size() > 1) {
    Node * tmp1 = pq.top();
    pq.pop();
    Node * tmp2 = pq.top();
    pq.pop();
    pq.push(new Node(tmp1,tmp2));
  }
  return pq.top();
  //WRITE ME!
}  
