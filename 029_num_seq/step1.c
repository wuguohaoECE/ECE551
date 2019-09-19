// This file is for Step 1.
// You should do
//  Step 1 (A): write seq1
//  Step 1 (B): write main to test seq1
//  Step 1 (C): write printSeq1Range
//  Step 1 (D): add test cases to main to test printSeq1Range
//
// Be sure to #include any header files you need!
#include <stdio.h>

int seq1(int x){
  return -3+4*x;
}

void printSeq1Range(int low, int high){
  if(low<high){
    for(int i=low;i<high-1;i++){
      printf("%d, ",seq1(i));
    }
    printf("%d\n",seq1(high-1));
  }
  else{
    printf("\n");
  }
}

int main(){
  for(int i=-5;i<5;i++){
    printf("seq1(%d) = %d\n",i,seq1(i));
  }
  
  printf("printSeq1Range(%d, %d)\n",1,4);
  printSeq1Range(1,4);
  printf("printSeq1Range(%d, %d)\n",-4,-1);
  printSeq1Range(-4,-1);

  printf("printSeq1Range(%d, %d)\n",0,0);
  printSeq1Range(0,0);
  printf("printSeq1Range(%d, %d)\n",-1,-4);
  printSeq1Range(-1,-4);
  printf("printSeq1Range(%d, %d)\n",4,1);
  printSeq1Range(4,1);
}
