#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int *array,size_t n){
  if(n==0){return 0;}
  else{
    size_t max=1;
    size_t new_max=1;
    for(int i=1;i<n;i++){
      if(array[i]>array[i-1]){
	new_max++;
	if(new_max>max){
	  max=new_max;
	}
      }
      else{
	new_max=1;
      }
    }
    return max;
  }
}
	
