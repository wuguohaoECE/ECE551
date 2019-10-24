#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
void printSort(istream& ifs) {
  vector<string> Vec;
  while (1){
    string str;
    getline(ifs,str);
    if ( ifs.eof() ){
      break;
    }
    Vec.push_back(str);
  }
  sort(Vec.begin(), Vec.end());
  for(size_t i = 0; i < Vec.size(); i++){
    cout << Vec[i] << "\n";
  }
}
int main(int argc, char ** argv){
  if (argc < 2) {
    printSort(cin);
  }
  else {
    for(int i = 1; i < argc; i++){
      ifstream ifs;
      ifs.open (argv[i], ifstream::in);
      if ( !ifs.is_open() ){
	cout << "Error opening file" << endl;
	return EXIT_FAILURE;
      }
      printSort(ifs);
    }
  }
  return EXIT_SUCCESS;
}
    
