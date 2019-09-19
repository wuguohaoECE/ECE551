// This file is for Step 3.
// You should do
//  Step 3 (A): write seq3
//  Step 3 (B): write main to test seq3
//  Step 3 (C): write countEvenInSeq3Range
//  Step 3 (D): add test cases to main to test countEvenInSeq3Range
//
// Be sure to #include any header files you need!
#include <stdio.h>
#include <stdlib.h>
int seq3(int x, int y){
  return 6+(-2-x)*(3-y);
}

int countEvenInSeq3Range(int xLow,int xHi,int yLow,int yHi,int (*seq3)(int,int)){
  if((xLow<xHi)&(yLow<yHi)){   
    int count = 0;
    for(int i=xLow;i<xHi;i++){
      for(int j=yLow;j<yHi;j++){
	if(seq3(i,j)%2==0){
	  count++;
	}
      }  
    }
    return count;
  }
  else{return 0;}
}
int main(){
  for(int i=-5;i<6;i++){
    for(int j=-5;j<6;j++){
      printf("seq3(%d, %d) = %d\n",i,j,seq3(i,j));
    }
  }
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",0,2,0,3,countEvenInSeq3Range(0,2,0,3,seq3));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",-5,6,0,1,countEvenInSeq3Range(-5,6,0,1,seq3));
  return EXIT_SUCCESS;
  
}
