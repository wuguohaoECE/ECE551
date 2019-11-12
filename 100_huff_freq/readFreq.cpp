#include <stdio.h>
#include <cstdlib>
#include "readFreq.h"
#include <iostream>
#include <fstream>

using namespace std;
void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256 ) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  ifstream in(fname);
  string contents;
  if (in) {
    in.seekg(0, ios::end);
    size_t len = in.tellg();
    in.seekg(0);
    contents.resize(len + 1, '\0');
    in.read(&contents[0], len);
  }
  uint64_t * count = new uint64_t[257]();
  for (auto it = contents.begin(); it != contents.end(); ++it) {
    count[(int)*it]++;
  }
  return count;
}

