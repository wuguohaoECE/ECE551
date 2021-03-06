#include <cstdlib>
#include <cstdio>
#include <cmath>
#include "function.h"
int binarySearchForZero(Function<int, int> * f, int low, int high) {
  while(high - low > 1) {
    int mid = (high + low) / 2;
    int tmp = f->invoke(mid);
    if(tmp <= 0) {
      low = mid;
    }
    else{
      high = mid;
    }
  }
  return low;
}
