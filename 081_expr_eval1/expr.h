#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;
class Expression{
 public:
  virtual string toString() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression {
 private:
  long num;
 public:
 NumExpression(long a): num(a){}
  virtual string toString() const {
    string out;
    stringstream tmp;
    tmp << num;
    tmp >> out;
    return out;
  }
  virtual ~NumExpression() {}
};

class PlusExpression: public Expression {
 private:
  Expression * lhs;
  Expression * rhs;
 public:
 PlusExpression(Expression * a, Expression * b):lhs(a), rhs(b){}
  virtual string toString() const {
    string out;
    stringstream tmp;
    tmp << "(" << lhs->toString() << "+" << rhs->toString() << ")";
    tmp >> out;
    return out;
  }
  virtual ~PlusExpression() {
    delete lhs;
    delete rhs;
  }
};
