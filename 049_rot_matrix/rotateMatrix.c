#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rotate_matrix(char * rotate, char * pre, int size){
  for(int i = 0; i<10; i++){
    for(int j = 0; j<10; j++){
      rotate[j*size+9-i] = pre[i*size+j];
    }
    rotate[i*size+10]='\n';
    rotate[i*size+11]='\0';
  }
}

int main(int argc, char ** argv){
  if(argc != 2){
    fprintf(stderr, "Usage: please inputFIleName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if(f == NULL){
    perror("could not open file");
    return EXIT_FAILURE;
  }
  char pre_matrix[10][12];
  char * p = pre_matrix[0];
  int count = 0;
  while((p = fgets(p, 12, f)) != NULL){
    // printf("%s",p);
    //printf("%d\n",strchr(p,'\n')-p);
    //printf("count = %d\n",count);
    if(((strchr(p,'\n')-p != 10) & (count <=8)) | (count >= 10) ){
      fprintf(stderr,"plz input a 10*10 matrix\n");
      return EXIT_FAILURE;
    }
    p+=12;
    count++;
  }
  if(count < 10){
    fprintf(stderr,"plz input a 10*10 matrix\n");
    return EXIT_FAILURE;
  }
  char rotated_matrix[10][12];
  rotate_matrix(rotated_matrix[0], pre_matrix[0], 12);
  //printf("\n");
  for(int i = 0; i<10; i++){
    printf("%s",rotated_matrix[i]);
  }
  return EXIT_SUCCESS;
}

