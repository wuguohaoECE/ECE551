#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <vector>
using namespace std;

unordered_set<int> isDelete;

bool IsUniquePara(vector<string> & input) {
  unordered_set<string> test;
  for(auto it = input.begin(); it != input.end(); ++it) {
    if( test.count(*it) ) {
      return false;
    }
    else {
      test.insert(*it);
    }
  }
  return true;
}

int main(void) {
  vector<string> a;
  a.push_back("a");
  //a.push_back("a");
  a.push_back("r");
  // a.push_back("a");
  // a.push_back("r");
  a.push_back("d");
  if(IsUniquePara(a)) {
    cout << "unique" << endl;
  }
  return EXIT_SUCCESS;
}
