#include "bstset.h"
#include "assert.h"
int main(void) {
  
  BstSet<int> s1;
  s1.add(2);
  s1.add(1);
  s1.add(4);
  s1.add(6);
  s1.add(0.5);
  s1.add(7);
  s1.remove(4);
  assert(s1.contains(4) == false);
  return EXIT_SUCCESS;
}
