// This file is for Step 2.
// You should do
//  Step 2 (A): write seq2
//  Step 2 (B): write main to test seq2
//  Step 2 (C): write sumSeq2
//  Step 2 (D): add test cases to main to test sumSeq2
//
// Be sure to #include any header files you need!

#include <stdio.h>


int seq2(int x){
  int remainder = x%4;
  int quotient = x/4;
  if((x<0)&(remainder!=0)){quotient--;}
  if(remainder==1||remainder==-3)
  {
    return (-24+32*(quotient+1))*(quotient+1)/2+1;
  }
  else if(remainder==0)
  {
    quotient++;
    return (-40+32*quotient)*quotient/2+5;
  }
  else if(remainder==-1||remainder==3)
  {
    quotient=quotient+2;
    return (-56+32*quotient)*quotient/2+11;
  }
  else if(remainder==-2||remainder==2)
  {
    
    return 4+8*quotient;
  }
  return 0;
}

int sumSeq2(int low, int high){
	int result=0;
	if(high>low){
		for(int i=low;i<high;i++){
			result+=seq2(i);
		}
	}
	return result;
} 

int main(){
  for(int i=-10;i<15;i++){
    printf("seq2(%d) = %d\n",i,seq2(i));
  }
  printf("sumSeq2(%d, %d) = %d\n",0,2,sumSeq2(0,2));
  printf("sumSeq2(%d, %d) = %d\n",-3,2,sumSeq2(3,6));
  printf("sumSeq2(%d, %d) = %d\n",9,7,sumSeq2(9,7));
  
}
    
