#include<stdio.h>
#include<stdlib.h>
size_t maxSeq(int * array, size_t n);

int main(){
  int seq1[]={0};
  int seq2[]={5,4,3,2,1};
  int seq3[]={1,2,3,2,3,4,5};
  int seq4[]={4,3,2,1};
  int seq5[]={-4,-3,-2,1,2,3};
  int seq6[]={-4,-3,-2,-1,0,-1,2,3};
  int seq7[]={-4,-3,0,-1,1,2,3,4,5};
  int seq9[0];
  int seq10[12] = {1, 2, 3, 1, 2, 3, 4, 5, 1, 2, 3, 4};
  int seq11[] = {-1, -2, -3, 0, 3, 8};
  int seq12[] = {2,2,2,2};
  if(maxSeq(seq1,1)!=1||
     maxSeq(seq2,5)!=1||
     maxSeq(seq3,7)!=4||
     maxSeq(seq9,0)!=0||
     maxSeq(seq5,6)!=6||
     maxSeq(seq6,8)!=5||
     maxSeq(seq7,9)!=6||
     maxSeq(seq10,12)!=5||
     maxSeq(seq11,6)!=4||
     maxSeq(seq12,4)!=1
     ){return EXIT_FAILURE;}
  else{return EXIT_SUCCESS;}
}
  
  
