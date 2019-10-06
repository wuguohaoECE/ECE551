#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _kvpair_t {
  char * key;
  char * value;
  //DEFINE ME!

};
typedef struct _kvpair_t kvpair_t;

struct _kvarray_t {
  kvpair_t * kvarr;
  size_t len;
  //DEFINE ME!
};
typedef struct _kvarray_t kvarray_t;

typedef struct {
  char ** s;
  size_t len;
}char_t;
	
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
  printf("%d\n%d\n",kv->len,sizeof(*kv->kvarr));
  kv->kvarr = malloc(kv->len * sizeof(*kv->kvarr));
  for(int i = 0; i < kv->len; i++){
    break_kv(&(kv->kvarr[i]), file_char.s[i]);
    //printf("key = %d value = %s\n",(kv->kvarr)[i].key,file_char.s[i]);
  }
  return kv;
}

int main(void){
  kvarray_t * ans = readKVs("test.txt");
  printf("%ld\n",ans->len);
  for(int i = 0; i < ans->len; i++){
    printf("key = %s value = %s\n",ans->kvarr[i].key , ans->kvarr[i].value);
  }
  return EXIT_SUCCESS;
}
