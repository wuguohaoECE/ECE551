#include "function.h"
#include <tgmath.h>
using namespace std;


int binarySearchForZero(Function<int, int> * f, int low, int high);

void check(Function<int,int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  unsigned Max = 1;
  if( high > low ) {
    Max = log2(high - low) + 1;
  }
  CountedIntFn * WarpSin = new CountedIntFn(Max, f, mesg);
  int ans = binarySearchForZero(WarpSin, low, high);
  if (ans != expected_ans) {
    fprintf(stderr, "Computation is wrong\n");
    exit(EXIT_FAILURE);
  }
  return;
}

int main(void) {
  SinFunction * sinFunc = new SinFunction();

  check(sinFunc, 0, 100, 99, "SinFunction");
  check(sinFunc, 0, 1, 0, "SinFunction");
  check(sinFunc, -1, -1, -1, "SinFunction");
  check(sinFunc, 50000, 60000, 52359, "SinFunction");
  check(sinFunc, 60000, 70000, 60000, "SinFunction");
  check(sinFunc, 0, 150000, 52359, "sinfunc");
  check(sinFunc, 0, 104717, 52359, "sinfunc");
  return EXIT_SUCCESS;
}
