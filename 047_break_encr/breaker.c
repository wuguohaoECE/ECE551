#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int find_max(int * array, int size){
  int max = 0;
  for(int i = 1;i<size;i++){
    //printf("array[i]=%d,array[max]=%d\n",array[i],array[max]);
    if(array[i]>array[max]){
      max=i;
    }
  }
  return max;
}

int find_key(FILE * f,int * count,int size){
  int c;
  while((c = fgetc(f)) != EOF){
    //printf("%d  ",c);
    if(isalpha(c)){
      c -='a';
      count[c]++;
    }
    //printf("%d\n",c);
  }
  int max = find_max(count,size);
  max+='a';
  if(max>='e')
    {return max-'e';}
  else
    {return max-'e'+26;}
}

int main(int argc, char ** argv){
  if(argc != 2){
    fprintf(stderr,"Usage: please inputFileName\n");
    return EXIT_FAILURE;
  }
  // printf("%s\n",argv[1]);
  FILE * f = fopen(argv[1], "r");
  if(f == NULL){
    perror("could not open file");
    return EXIT_FAILURE;
  }
  int count[26]={0,0,0};
  int key = find_key(f,count,26);
  printf("%d\n",key);
  return EXIT_SUCCESS;
}

