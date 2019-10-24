#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
int main(int argc, char ** argv){
  for(int i = 1; i < argc; i++){
    ifstream f(argv[i], fstream::in);
    if( !f.is_open() ){
      cout << "open file failed" <<endl;
    }
    
