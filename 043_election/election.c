#include "election.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//include any other headers you need here...

int read_char(char * out,const char * in, char str,int index, int check){
  char * p1 = out;
  //char * p2 = in;
  int count = 0;
  while(in[index]!=str){
    if(count>64){
      fprintf(stderr,"you may miss something");
      exit(EXIT_FAILURE);
    }
    if( check == 1 ){
      if(in[index]<48 || in[index]>57){
	exit(EXIT_FAILURE);
      }
    }
    *p1=in[index];
    p1++;
    index++;
    count++;
  }
  index++;
  *p1='\0';
  return index;
}




state_t parseLine(const char * line) {
  //STEP 1: write me
  state_t state;
  int index = 0;
  index = read_char(state.name,line,':',index,0);
  //printf("test %s\n", state.name);
  char temp[64]; 
  index = read_char(temp,line,':',index,1);
  //printf("test %s\n", temp);
  if( ( state.population = atoi(temp) ) <= 0){
    exit(EXIT_FAILURE);
  }
  //state.population = atoi(temp);
  index = read_char(temp,line,'\0',index,1);
  //printf("test %s\n", temp);
  if( ( state.electoralVotes = atoi(temp) ) <= 0){
    exit(EXIT_FAILURE);
  }
  return state;
}

unsigned int countElectoralVotes(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 2: write me
  unsigned int count = 0;
  for(int i = 0; i < nStates; i++){
    if(voteCounts[i]*2 > stateData[i].population){
      count += stateData[i].electoralVotes;
    }
  }
  return count;
}

void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  float temp;
  for(int i = 0; i < nStates; i++){
    temp = (float)voteCounts[i]/stateData[i].population;
    if( (temp > 0.495) && (temp < 0.505) ){
      printf("%s requires a recount (Candidate A has %.2f%% of the vote)\n", stateData[i].name, temp*100);
    }
  }
  //STEP 3: write me
}

void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  float max = 0;
  int index = 0;
  float temp;
  for(int i = 0; i < nStates; i++){
    temp = (float)voteCounts[i]/stateData[i].population;
    if( temp > max ){
      max = temp;
      index = i;
    }
  }
  printf("Candidate A won %s with %.2f%% of the vote\n", stateData[index].name, max*100);
  //STEP 4: write me
}
