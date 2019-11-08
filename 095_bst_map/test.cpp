#include "bstmap.h"
#include <assert.h>
int main(void) {
  BstMap<int,int> m1;
  m1.add(2,2);
  m1.add(4,4);
  m1.add(1,1);
  m1.add(7,7);
  m1.add(3,3);
  m1.add(9,9);
  m1.add(-1,-1);
  m1.add(88,88);
  m1.add(17,17);
  m1.add(-23,-23);
  m1.add(16,16);
  m1.add(44,44);
  m1.add(77,77);
  cout << m1.lookup(4) << endl;
  cout << m1.lookup(1) << endl;
  cout << m1.lookup(7) << endl;
  cout << m1.lookup(2) << endl;
  cout << m1.lookup(9) << endl;
  cout << m1.lookup(-1) << endl;
  cout << m1.lookup(88) << endl;
  cout << m1.lookup(17) << endl;
  cout << m1.lookup(-23) << endl;
  cout << m1.lookup(16) << endl;
  cout << m1.lookup(44) << endl;
  cout << m1.lookup(77) << endl;
  m1.remove(2);
  cout << "after remove\n";
  //m1.print(m1.getroot());
  cout << m1.lookup(4) << endl;
  cout << m1.lookup(1) << endl;
  cout << m1.lookup(7) << endl;
  //cout << m1.lookup(2) << endl;
  cout << m1.lookup(9) << endl;
  cout << m1.lookup(-1) << endl;
  cout << m1.lookup(88) << endl;
  cout << m1.lookup(17) << endl;
  cout << m1.lookup(-23) << endl;
  cout << m1.lookup(16) << endl;
  cout << m1.lookup(44) << endl;
  cout << m1.lookup(77) << endl;
  assert(m1.lookup(4) == 4);
  assert(m1.lookup(1) == 1);
  assert(m1.lookup(7) == 7);
  assert(m1.lookup(3) == 3);
  assert(m1.lookup(9) == 9);
  assert(m1.lookup(-1) == -1);
  assert(m1.lookup(88) == 88);
  assert(m1.lookup(17) == 17);
  assert(m1.lookup(-23) == -23);
  assert(m1.lookup(16) == 16);
  assert(m1.lookup(44) == 44);
  assert(m1.lookup(77) == 77);
  
  
  return EXIT_SUCCESS;
}
