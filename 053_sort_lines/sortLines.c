#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}


char ** read_file(FILE * f, size_t * strings_size){
  char ** p = malloc( (*strings_size+1) * sizeof( *p ) );
  p[*strings_size]=NULL;
  size_t n = 0;
  while( getline( &p[*strings_size], &n, f )>=0 ){
    (*strings_size)++;
    p = realloc( p, (*strings_size+1)*sizeof(*p) );
    p[*strings_size]=NULL;
    n=0;
  }
  sortData(p, *strings_size);
  return p;
}
    

void print_char(char ** array, size_t strings_size){
  for(int j = 0; j < strings_size; j++){
      printf("%s", array[j]);
      free(array[j]);
    }
  free(array);
}

int main(int argc, char ** argv) {
  size_t strings_size = 0;
  char ** array;
  if(argc==1){
    array = read_file(stdin, &strings_size);
    print_char(array, strings_size);
  }
  if(argc>1){
    FILE * f;
    for(int i = 1; i < argc; i++){
      strings_size = 0;
      f = fopen(argv[i], "r");
      if( f == NULL ){
        perror("The error was");
	return EXIT_FAILURE;
      }
      array = read_file(f, &strings_size);
      print_char(array, strings_size);
    }
  }
  return EXIT_SUCCESS;
}
      
