#include "election.h"
//include any other headers you need here...

void read_char(char * out, char * in, char str){
  char * p1 = out;
  char * p2 = in;
  int count = 0;
  while(*p2!=str){
    if(count>=64){
      fprintf(stderr,"you may miss something");
      return EXIT_FAILURE;
    }
    *p1=*p2;
    p1++;
    p2++;
    count++;
  }
}


state_t parseLine(const char * line) {
  //STEP 1: write me
  state_t 
}

unsigned int countElectoralVotes(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 2: write me
  return 0;
}

void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 3: write me
}

void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 4: write me
}
