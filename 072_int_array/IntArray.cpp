#include "IntArray.h"
#include <assert.h>
#include <ostream>

IntArray::IntArray(): data(NULL), numElements(0) {}
IntArray::IntArray(int n): data(new int[n]), numElements(n) {}

IntArray::IntArray(const IntArray & rhs): data(new int[rhs.numElements]), numElements(rhs.numElements){
  for(int i = 0; i < numElements; i++){
    data[i] = rhs.data[i];
  }
}
IntArray::~IntArray() {
  delete[] data;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
  if(this != &rhs){
    int * temp = new int[rhs.size()];
    for(int i = 0; i < rhs.size(); i++){
      temp[i] = rhs.data[i];
    }
    delete[] data;
    data = temp;
    numElements = rhs.size();
  }
  return *this;
}
const int & IntArray::operator[](int index) const {
  return data[index];
}
int & IntArray::operator[](int index) {
  return data[index];
}

int IntArray::size() const {
  return numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
  if(numElements != rhs.numElements){
    return false;
  }
  for(int i = 0; i < numElements; i++){
    if(data[i] != rhs[i]){
      return false;
    }
  }
  return true;
}

bool IntArray::operator!=(const IntArray & rhs) const {
  return !(*this == rhs);
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  if (rhs.size() == 0) {
    s << "{}";
    return s;
  }

  s << "{";
  for (int i = 0; i < rhs.size() - 1; i++) {
    s << rhs[i] << ", ";
  }
  s << rhs[rhs.size() - 1] << "}";
  return s;
}
