#include <stdio.h>
#include <stdlib.h>

unsigned power (unsigned x, unsigned y);

int run_check(unsigned x, unsigned y, unsigned expected_ans){
  unsigned ans = power(x,y);
  if (ans!=expected_ans){
    return(EXIT_FAILURE);
  }
  return(EXIT_SUCCESS);
}

int main(void){
  if( run_check(2,2,4)|| 
  run_check(8,1,8)||
  run_check(0,1,0)||
  run_check(0,0,1)||
  run_check(2,16,65536)||
  run_check(1,2,1)||
      run_check(1,2,1)){
    return(EXIT_FAILURE);
  }
  
  return(EXIT_SUCCESS);
 }
