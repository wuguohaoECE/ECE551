#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <vector>


//YOUR CODE GOES HERE!
using namespace std;
template<typename T>
class Matrix {
 private:
  int nR;
  int nC;
  vector<T> ** rows;
 public:
 Matrix():
  nR(0),
    nC(0),
    rows(NULL){}
 Matrix(int r, int c):
  nR(r),
    nC(c),
    rows(new vector<T> *[r]){
    for(int i = 0; i < r; i++){
      rows[i] = new vector<T>(c);
    }
  }
  Matrix(const Matrix & rhs):
  nR(rhs.nR),
    nC(rhs.nC),
    rows(new vector<T> *[nR]){
    for(int i = 0; i < nR; i++){
      rows[i] = new vector<T>(rhs[i]);
    }
  }
  ~Matrix() {
    for(int i = 0; i < nR; i++){
      delete rows[i];
    }
    delete[] rows;
  }
  Matrix & operator=(const Matrix & rhs) {
    if(this != &rhs){
      vector<T> ** tmp = new vector<T> *[rhs.nR];
      for(int i = 0; i < rhs.nR; i++){
	tmp[i] = new vector<T>(rhs[i]);
      }
      for(int i = 0; i < nR; i++){
	delete rows[i];
      }
      delete[] rows;
      rows = tmp;
      nR= rhs.nR;
      nC= rhs.nC;
    }
    return *this;
  }
  //return row
  int getRows() const { return nR; }

  //return column
  int getColumns() const { return nC; }

  //[]operator
  const std::vector<T> & operator[](int index) const {
    assert(index >= 0 && index < nR);
    return *rows[index];
  }

  std::vector<T> & operator[](int index) {
    assert(index >= 0 && index < nR);
    return *rows[index];
  }

  //==operator
  bool operator==(const Matrix & rhs) const {
    if (nR != rhs.nR || nC != rhs.nC) {
      return false;
    }
    for (int i = 0; i < nR; i++) {
      if ((*this)[i] != rhs[i]) {
        return false;
      }
    }
    return true;
  }

  //+operator
  Matrix operator+(const Matrix & rhs) const {
    assert(nR == rhs.nR && nC == rhs.nC);
    Matrix ans(nR, nC);
    ans.nR = nR;
    ans.nC = rhs.nC;
    for (int i = 0; i < nR; i++) {
      for (int j = 0; j < nC; j++) {
        ans[i][j] = (*this)[i][j] + rhs[i][j];
      }
    }
    return ans;
  }
};

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  if (rhs.getRows() == 0) {
    s << "[  ]";
    return s;
  }
  s << "[ ";
  for (int i = 0; i < rhs.getRows() - 1; i++) {
    s << rhs[i] << ",\n";
  }
  s << rhs[rhs.getRows() - 1] << " ]";
  return s;
}

template<typename T>
std::ostream & operator<<(std::ostream & s, const std::vector<T> & rhs) {
  if (rhs.size() == 0) {
    s << "{  }";
    return s;
  }
  s << "{ ";
  for (size_t i = 0; i < rhs.size() - 1; i++) {
    s << rhs[i] << ",";
  }
  s << rhs[rhs.size() - 1] << " }";
  return s;
}
#endif
