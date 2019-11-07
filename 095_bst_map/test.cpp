#include "bstmap.h"

int main(void) {
  BstMap<int,int> m1;
  m1.add(1,2);
  m1.add(10,10);
  m1.add(5,5);
  m1.add(6,8);
  m1.add(4,2);
  m1.add(12,1);
  cout << m1.lookup(5) << endl;
  m1.remove(10);
  cout << m1.lookup(6) << endl;
  
  cout << m1.lookup(5) << endl;
  
  cout << m1.lookup(12) << endl;
  
  cout << m1.lookup(4) << endl;
  
  
  return EXIT_SUCCESS;
}
