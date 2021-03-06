#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"


    
	
char_t read_file(FILE * f){
  char_t ans;
  ans.len = 1;
  ans.s = malloc( ans.len * sizeof(*ans.s) );
  size_t sz = 0;
  ans.s[ans.len-1] = NULL;
  while(  getline(&ans.s[ans.len - 1], &sz, f) >= 0 ){
    ans.len++;
    ans.s = realloc(ans.s, ans.len * sizeof(*ans.s));
    ans.s[ans.len-1] = NULL;
  }
  free(ans.s[ans.len-1]);
  ans.len--;
  return ans;
}

void break_kv(kvpair_t * out, char * in ){
  char * id1 = strchr(in,'=');
  char * id2 = strchr(in,'\n');
  *id1 = '\0';
  *id2 = '\0';
  out->key = in;
  out->value = id1+1;
  //printf("key = %d value = %s\n",out->key,out->value);
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    return NULL;
  }
  char_t file_char = read_file(f);
  kvarray_t * kv = malloc(sizeof(*kv));
  kv->len = file_char.len;
  //printf("%ld\n%ld\n",kv->len,sizeof(*kv->kvarr));
  kv->kvarr = malloc(kv->len * sizeof(*kv->kvarr));
  for(int i = 0; i < kv->len; i++){
    break_kv(&(kv->kvarr[i]), file_char.s[i]);
    // printf("key = %s value = %s\n",(kv->kvarr)[i].key,file_char.s[i]);
  }
  free(file_char.s);
  fclose(f);
  return kv;
}

void freeKVs(kvarray_t * pairs) {
  for(int i = 0; i < pairs->len; i++){
    free(pairs->kvarr[i].key);
  }
  free(pairs->kvarr);
  free(pairs);
  //WRITE ME
}

void printKVs(kvarray_t * pairs) {
  for(int i = 0; i < pairs->len; i++){
    printf("key = '%s' value = '%s'\n", pairs->kvarr[i].key, pairs->kvarr[i].value);
  }
  //WRITE ME
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  char * ans = NULL;
  for(int i = 0; i < pairs->len; i++){
    if( strcmp(pairs->kvarr[i].key, key) == 0 ){
      ans = pairs->kvarr[i].value;
      break;
    }
  }
  return ans;
}
