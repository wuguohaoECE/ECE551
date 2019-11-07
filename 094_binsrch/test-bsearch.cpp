#include "function.h"
#include <cmath>
#include <iostream>
using namespace std;


int binarySearchForZero(Function<int, int> * f, int low, int high); 

class CountedIntFn : public Function<int,int>{
protected:
  unsigned remaining;
  Function<int,int> * f;
  const char * mesg;
public:
  CountedIntFn(unsigned n, Function<int,int> * fn, const char * m): remaining(n),
                                                                    f(fn),
                                                                    mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr,"Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }

};

class SinFunction : public Function<int, int> {
public:
  virtual int invoke(int arg) {
    return 10000000 * (sin(arg/100000.0) - 0.5);
  }
};

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
  cout << ans << endl;
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
