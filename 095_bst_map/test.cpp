#include "bstmap.h"

int main(void) {
  BstMap<int,int> m1;
  m1.add(1,2);
  m1.add(10,10);
  m1.add(5,5);
  m1.add(6,8);
  m1.add(4,2);
  m1.add(12,1);
  BstMap<int,int> m2(m1);
  BstMap<int,int> m3;
  m3 = m2;
  m3.print(m3.getroot());
  m1.print(m1.getroot());
  
  m2.print(m2.getroot());
  m1.add(7,2);
  cout << m1.lookup(5) << endl;
  m1.remove(1);
  //cout << m1.lookup(6) << endl;
  
  cout << m1.lookup(5) << endl;
  
  cout << m1.lookup(12) << endl;
  
  cout << m1.lookup(4) << endl;
  cout << m1.lookup(10);

  //cout << m1.lookup(7);
  
  return EXIT_SUCCESS;
}
