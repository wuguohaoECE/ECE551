#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"
char_t out_file(FILE * f){
  char_t ans = read_file(f);
  char * id;
  for(int i = 0; i < ans.len; i++){
    id = strchr(ans.s[i], '\n');
    *id = '\0';
  }
  return ans;
}

void free_file(char_t in){
  for(int i = 0; i< in.len; i++){
    free(in.s[i]);
  }
  free(in.s);
}

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE * f = fopen(filename, "r");
  if( f == NULL ){
    return NULL;
  }
  char_t in = out_file(f);
  if( fclose(f) != 0 ){
    printf("close file failure");
    return NULL;
  }
  counts_t * ans = createCounts();
  for(int i = 0; i < in.len; i++){
    addCount(ans, lookupValue(kvPairs, in.s[i]) );
  }
  free_file(in);
  return ans;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
 //read the key/value pairs from the file named by argv[1] (call the result kv)
  if( argc<3 ){
    printf("plz put files");
    return EXIT_FAILURE;
  }
  kvarray_t * kv = readKVs(argv[1]);
  if (kv == NULL){
    printf("read kv failure");
    return EXIT_FAILURE;
  }
 //count from 2 to argc (call the number you count i)
  counts_t * c;
  for( int i = 2; i < argc; i++){
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    c = countFile(argv[i],kv);
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);

    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    if( fclose(f) != 0 ){
      printf("close file failure");
      EXIT_FAILURE;
    }
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }
 //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
