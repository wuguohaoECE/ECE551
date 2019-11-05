#include "il.h"
#include <cstdlib>
#include <cstdio>
#include <assert.h>
void testList(void) {
  IntList l1;
  assert( (l1.getSize() == 0) &&
	  (l1.size == 0) &&
	  (l1.head == NULL) &&
	  (l1.tail == NULL) );
  // 2
  l1.addBack(2);
  assert( (l1.head->data == l1[0]) &&
	  (l1.head == l1.tail) &&
	  (l1.getSize() == 1) &&
	  (l1.size == 1) &&
	  (l1.head != NULL) &&
	  (l1.find(2) == 0) );
  // 2 3
  l1.addBack(3);
  assert( (l1.head->data == l1[0]) &
	  (l1.head->next->data == l1[1]) &
	  (l1.tail == l1.head->next) &&
	  (l1.getSize() == 2) &&
	  (l1.find(2) == 0) &&
	  (l1.find(3) == 1) );
  // 4 2 3
  l1.addFront(4);
  assert( (l1.head->data == 4) &&
	  (l1.head->next->data == 2) &&
	  (l1.head->next->next->data == 3) &&
	  (l1.getSize() == 3) &&
	  (l1.find(4) == 0) &&
	  (l1[0] == 4) &&
	  (l1[2] == 3) &&
	  (l1.head == l1.tail->prev->prev) );
  IntList l2;
  l2 = l1;
  assert( (l2.head->data == 4) &&
	  (l2.head->next->data == 2) &&
	  (l2.head->next->next->data == 3) &&
	  (l2.getSize() == 3) &&
	  (l2.find(4) == 0) &&
	  (l2[0] == 4) &&
	  (l2[2] == 3) &&
	  (l2.head == l2.tail->prev->prev) );
  IntList l3(l2);
  assert( (l3.head->data == 4) &&
	  (l3.head->next->data == 2) &&
	  (l3.head->next->next->data == 3) &&
	  (l3.getSize() == 3) &&
	  (l3.find(4) == 0) &&
	  (l3[0] == 4) &&
	  (l3[2] == 3) &&
	  (l3.head == l3.tail->prev->prev) );  
  // 4 2 3 fail to remove 5
  assert( l1.remove(5) == false );
  // 4 3 successfully remove 2
  bool x = l1.remove(2);
  assert( (x == true) &&
	  (l1.size == 2) &&
	  (l1.getSize() == 2) &&
	  (l1[0] == 4) &&
	  (l1[1] == 3) &&
	  (l1.head->data == 4) &&
	  (l1.tail->data == 3) &&
	  (l1.head->next == l1.tail) &&
	  (l1.find(2) == -1) &&
	  (l1.head->next->next == NULL));
  l1.remove(4);
  // 3
  assert( (l1.size == 1) &&
	  (l1.getSize() == 1) &&
	  (l1.head == l1.tail) &&
	  (l1.head->data == l1.tail->data) &&
	  (l1.head->next == NULL) &&
	  (l1.tail->prev == NULL) );
  l1.remove(3);
  assert( (l1.size == 0) &&
	  (l1.head == NULL) &&
	  (l1.head == l1.tail));

  // 0 1 2 ....9 
  for (int i = 0; i < 10; i++) {
    l1.addBack(i);
  }
  for (int i = 0; i < 10; i++) {
    if (l1[i] != i) {
      assert(0);
    }
  }
  l1[1] = 10;
  assert(l1[1] == 10);
  assert(l1.head->next->data == 10);
  l1[1] = 1;
  assert(l1.size == 10);
  assert(l1.getSize() == 10);
  IntList list1 = l1;
  list1 = list1;
  for (int i = 0; i < 10; i++) {
    if (list1[i] != i) {
      assert(0);
    }
  }
  //-----------------------
  IntList list2 = list1;
  assert(list1.head != list2.head);
  assert(list1.head->next != list2.head->next);
  assert(list1.tail != list2.tail);
  assert(list1.tail->next == NULL);
  assert(list1.head->data == 0);
  assert(list1.tail->data == 9);

  assert(list1.size == 10);
  assert(list1.head->next != list2.head->next);
  assert(list1.tail->next == NULL);
  assert(list1.head->prev == NULL);
  assert(list1.tail->prev != list2.head->prev);

  assert(list1.head->next->data == 1);
  assert(list1.getSize() == list1.size);
  assert(list1.find(5) == 5);

  ////////////////////////
  IntList list5(list2);

  assert(list5.head != list2.head);
  assert(list5.head->next != list2.head->next);
  assert(list5.tail != list2.tail);
  assert(list5.tail->next == NULL);
  assert(list5.head->data == 0);
  assert(list5.tail->data == 9);

  assert(list5.size == 10);
  assert(list5.head->next != list2.head->next);
  assert(list5.tail->next == NULL);
  assert(list5.head->prev == NULL);
  assert(list5.tail->prev != list2.head->prev);
  assert(list5.head->next->data == 1);
  assert(list5.getSize() == list1.size);
  assert(list5.find(5) == 5);
  //-----------------------------------------------
  IntList list10;
  list10.addFront(1);
  assert(list10.head == list10.tail);
  assert(list10.head->next == NULL);
  assert(list10.tail->prev == NULL);

  list10[0] = 10;
  assert(list10[0] == 10);
  assert(list10.head->data == 10);
  list2[1] = 1;

  IntList list11(list10);
  assert(list10.size == list11.getSize());
  assert(list11.head != list10.head);
  assert(list11.tail != list10.tail);
  assert(list11.head == list11.tail);
  assert(list11.head->next == NULL);
  assert(list11.tail->next == NULL);
  assert(list11.head->prev == NULL);
  assert(list11.tail->prev == NULL);

  IntList list12 = list10;
  assert(list10.size == list12.getSize());
  assert(list12.head != list10.head);
  assert(list12.tail != list10.tail);
  assert(list12.head == list12.tail);
  assert(list12.head->next == NULL);
  assert(list12.tail->next == NULL);
  assert(list12.head->prev == NULL);
  assert(list12.tail->prev == NULL);
  // testcase12
  //list1 = list10;
  
  IntList l9;
  l9.addFront(1);
  l9.addFront(2);
  IntList l10;
  l10.addFront(1);
  l10 = l9;

}

int main(void) {
  testList();
  return EXIT_SUCCESS;
}
