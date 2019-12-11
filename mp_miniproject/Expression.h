#include <string>
#include <map>
#include <unordered_set>
// The structure I design is:
/*
Expression{
  parameterExpression : string paraName; Expression * paraMaterial
  functionExpression : string fname; vector<parameterExpression *> parameters; Expression * function;
  numericExpression : double numValue;
  singleFunctionExpression : Expression * theExpression; string FunctionName; {
                                                                  floorFunction;
								  ceilFunction;
								  roundFunction;
								  }
  OperatorExpression : Expression * lhs; Expression * rhs; const char *operatorr; {
                                                                  PlusExpression
								  MinusExpression
								  TimesExpression
								  DivExpression
								  ModExpression
 								  PowExpression
								  LogbExpression
								  }
  SelectExpression : Expression * lhs; Expression * rhs; const char *operatorr						 




 */


using namespace std;

//this set is used to record and differentiate function expression, parameter expression and other expression, in order to avoid double detele
//In particular, FunctionExpression can only be destructed by itself. And ParameterExpression can only be destructed by its FunctionExpression
unordered_set<void*> isDelete;


class Expression
{
 public:
  virtual ~Expression() {}
  virtual double evaluate() const = 0;
};


class parameterExpression : public Expression
{
 private:
  std::string paraName;
  Expression * paraMaterial;
  
 public:
  parameterExpression(std::string name, Expression * expr) : paraName(name), paraMaterial(expr) {}
  virtual ~parameterExpression() {
    if (paraMaterial != NULL &&
	!::isDelete.count(paraMaterial) ) {
      delete paraMaterial;
      paraMaterial = NULL;
    }
  }
  virtual double evaluate() const {
    return paraMaterial->evaluate();
  }
  const string & getParaName() const {return paraName;}
  void setMaterial(Expression * expr) {
    if(paraMaterial != NULL &&
       !::isDelete.count(paraMaterial) ) {
      delete paraMaterial;
    }
    paraMaterial = expr;
  }
  
};

class numericExpression : public Expression
{
 private:
  double numValue;
 public:
  numericExpression(double num) : numValue(num) {}
  virtual ~numericExpression() {}
  virtual double evaluate() const {
    return numValue;
  }
};

class functionExpression : public Expression
{
 private:
  std::string fname;
  std::vector<parameterExpression *> parameters;
  Expression * function;
 public:
  functionExpression(std::string fname,
                     std::vector<parameterExpression *> parameters,
                     Expression * function) :
  fname(fname),
    parameters(parameters),
    function(function) {}
  virtual double evaluate() const {
    return function->evaluate();
  }
  double evaluateFromNumPara(vector<double> & para) {
    if(para.size() == parameters.size()) {
      for(size_t i = 0; i < para.size(); i++) {
	Expression * num = new numericExpression(para[i]);
	parameters[i]->setMaterial(num);
      }
      return evaluate();
    }
    throw exception();
  }
  string getName() { return fname;}
  size_t getLength() { return parameters.size(); }
  void setFunctionExpression(Expression * expr) { function = expr; }
  vector<parameterExpression *> getParas() { return parameters; }
  virtual ~functionExpression() {
    if (function != NULL &&
	!::isDelete.count(function) ) {
      delete function;
      function = NULL;
    }
    for (size_t i = 0; i < parameters.size(); i++) {
      delete parameters[i];
      parameters[i] = NULL;
    }
  }
};




class singleFunctionExpression : public Expression
{
 protected:
  Expression * theExpression;
  std::string FunctionName;
 public:
 singleFunctionExpression(Expression * the, std::string name) :
  theExpression(the),
    FunctionName(name) {}
  
  virtual ~singleFunctionExpression() {
    if(theExpression != NULL &&
       !::isDelete.count(theExpression) ) {
      delete theExpression;
      theExpression = NULL;
    }
  }
  virtual double evaluate() const = 0;
};

class floorFunction : public singleFunctionExpression
{
 public:
 floorFunction(Expression * the) : singleFunctionExpression(the, "floor"){}
  virtual double evaluate() const {
    return floor(theExpression->evaluate());
  }

  virtual ~floorFunction() {}
};

class ceilFunction : public singleFunctionExpression
{
 public:
 ceilFunction(Expression * the) : singleFunctionExpression(the, "ceil"){}
  virtual double evaluate() const  {
    return ceil(theExpression->evaluate());
  }
  virtual ~ceilFunction() {}
  
};

class roundFunction : public singleFunctionExpression
{
 public:
 roundFunction(Expression * the) : singleFunctionExpression(the, "round"){}
  virtual double evaluate() const {
    return round(theExpression->evaluate());
  }
  virtual ~roundFunction() {}
};


class OperatorExpression : public Expression
{
 protected:
  Expression * lhs;
  Expression * rhs;
  const char * operatorr;

 public:
  OperatorExpression(Expression * lhs, Expression * rhs, const char * operat) :
  lhs(lhs),
    rhs(rhs),
    operatorr(operat) {}
  virtual ~OperatorExpression(){
    if (lhs != NULL &&
	!::isDelete.count(lhs) ) {
      delete lhs;
      lhs = NULL;
    }
    if (rhs != NULL &&
	!::isDelete.count(rhs) ) {
      delete rhs;
      rhs = NULL;
    }
  }
  virtual double evaluate() const = 0;
  
    
};
    
    
class PlusExpression : public OperatorExpression
{
 public:
  PlusExpression(Expression * lhs, Expression * rhs) : OperatorExpression(lhs, rhs, "+") {}
virtual double evaluate() const { return lhs->evaluate() + rhs->evaluate(); }
  virtual ~PlusExpression(){}
};
class MinusExpression : public OperatorExpression
{
 public:
  MinusExpression(Expression * lhs, Expression * rhs) : OperatorExpression(lhs, rhs, "-") {}
  virtual double evaluate() const { return lhs->evaluate() - rhs->evaluate(); }
  virtual ~MinusExpression(){}
};
class TimesExpression : public OperatorExpression
{
 public:
  TimesExpression(Expression * lhs, Expression * rhs) : OperatorExpression(lhs, rhs, "*") {}
  virtual double evaluate() const { return lhs->evaluate() * rhs->evaluate(); }
  virtual ~TimesExpression(){}
};
class DivExpression : public OperatorExpression
{
 public:
  DivExpression(Expression * lhs, Expression * rhs) : OperatorExpression(lhs, rhs, "/") {}
  virtual double evaluate() const { return lhs->evaluate() / rhs->evaluate(); }
  virtual ~DivExpression(){}
};
class ModExpression : public OperatorExpression
{
 public:
  ModExpression(Expression * lhs, Expression * rhs) : OperatorExpression(lhs, rhs, "/") {}
  virtual ~ModExpression(){}
  virtual double evaluate() const {
    return (int)lhs->evaluate() % (int)rhs->evaluate();
  }
  
};

class PowExpression : public OperatorExpression
{
 public:
 PowExpression(Expression * lhs, Expression * rhs) : OperatorExpression(lhs, rhs, "^") {}
  virtual ~PowExpression(){}
  virtual double evaluate() const {
    return pow(lhs->evaluate(), rhs->evaluate());
  }
  
};

class LogbExpression : public OperatorExpression
{
 public:
 LogbExpression(Expression * lhs, Expression * rhs) : OperatorExpression(lhs, rhs, "Logb") {}
  virtual ~LogbExpression(){}
  virtual double evaluate() const {
    return log(rhs->evaluate()) / log(lhs->evaluate());
  }
  
};

class SelectExpression : public Expression
{
 private:
  Expression * lhs;
  Expression * mhs;
  Expression * rhs;
 public:
 SelectExpression(Expression * lhs, Expression * mhs, Expression * rhs):lhs(lhs), mhs(mhs),rhs(rhs){}
  virtual ~SelectExpression(){
    if (lhs != NULL &&
	!::isDelete.count(lhs) ) {
      delete lhs;
      lhs = NULL;
    }
    if (mhs != NULL &&
	!::isDelete.count(mhs) ) {
      delete mhs;
      mhs = NULL;
    }
    if (rhs != NULL &&
	!::isDelete.count(rhs) ) {
      delete rhs;
      rhs = NULL;
    }
  }
  
  virtual double evaluate() const {
    if(lhs->evaluate() >= 0) {
      return mhs->evaluate();
    }
    return rhs->evaluate();
  }
  
};
