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

class OpsExpression: public Expression{
 protected:
  Expression * lhs;
  Expression * rhs;
  
 public:
 OpsExpression(Expression * a, Expression * b):lhs(a), rhs(b){}
  virtual ~OpsExpression() {
    delete lhs;
    delete rhs;
  }
};

class PlusExpression: public OpsExpression {

 public:
 PlusExpression(Expression * a, Expression * b):OpsExpression(a,b){}
  virtual string toString() const {
    string out;
    stringstream tmp;
    tmp << "(" << lhs->toString() << "+" << rhs->toString() << ")";
    tmp >> out;
    return out;
  }
};

class MinusExpression: public OpsExpression {

 public:
 MinusExpression(Expression * a, Expression * b):OpsExpression(a,b){}
  virtual string toString() const {
    string out;
    stringstream tmp;
    tmp << "(" << lhs->toString() << "-" << rhs->toString() << ")";
    tmp >> out;
    return out;
  }
};

class TimesExpression: public OpsExpression {

 public:
 TimesExpression(Expression * a, Expression * b):OpsExpression(a,b){}
  virtual string toString() const {
    string out;
    stringstream tmp;
    tmp << "(" << lhs->toString() << "*" << rhs->toString() << ")";
    tmp >> out;
    return out;
  }
};

class DivExpression: public OpsExpression {

 public:
 DivExpression(Expression * a, Expression * b):OpsExpression(a,b){}
  virtual string toString() const {
    string out;
    stringstream tmp;
    tmp << "(" << lhs->toString() << "/" << rhs->toString() << ")";
    tmp >> out;
    return out;
  }
};
