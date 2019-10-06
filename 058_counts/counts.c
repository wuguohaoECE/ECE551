#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
  counts_t * ans = malloc(sizeof(*ans));
  ans->len = 0;
  return ans;
  //WRITE ME
}
void addCount(counts_t * c, const char * name) {
  if(name == NULL){
    addCount(c, "<unKnown> ");
    return;
  }
  for(int i = 0; i < c->len; i++){
    if( (strcmp( c->carr[i].chr, name ) == 0) ){
      c->carr[i].n++;
      return;
    }
  }
  c->len++;
  if(c->len == 1){
    c->carr = malloc(sizeof(*c->carr));
  }
  else{
    if( (c->carr=realloc(c->carr, c->len * sizeof(*c->carr))) == NULL ){
      printf("realloc failure");
      return;
    } 
  }
  c->carr[c->len-1].n = 1;
  c->carr[c->len-1].chr = name;
  //WRITE ME
}
void printCounts(counts_t * c, FILE * outFile) {
  int sign = 0;
  int id;
  for(int i = 0; i < c->len; i++){
    if( strcmp(c->carr[i].chr,"<unKnown> ") == 0 ){
      sign = 1;
      id = i;
      continue;
    }
    fprintf(outFile, "%s: %d\n", c->carr[i].chr,c->carr[i].n);
  }
  if(sign == 1){
    fprintf(outFile, "%s: %d\n", c->carr[id].chr,c->carr[id].n);
  }
  //WRITE ME
}

void freeCounts(counts_t * c) {
  free(c->carr);
  free(c);
  //WRITE ME
}
