#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <stack>
#include <vector>

#include "Expression.h"
#include <exception>
using namespace std;

//  input: reference of string with space at the front
//  output: string with no space at the front
void StringSkipSpace(string & inputString) {
  for(size_t i = 0; i < inputString.size();i++) {
    if( isspace(inputString[i]) ) {
      inputString.erase(i,1);
      i--;
    }
    else{
      break;
    }
  }
}

// given a string, find the length from the beginning to next "space","(",")"
int FindWordLength(const string & inputString) {
  int length = 0;
  for(size_t i = 0; i < inputString.size();i++) {
    if( !isspace(inputString[i]) && (inputString[i] != '\0') && 
	(inputString[i] != '(') && (inputString[i] != ')') ) {
      length++;
    }
    else {
      return length;
    }
  }
  return length;
}
//Function prototype
Expression * ParseExpression(string & inputString,
		map<string, functionExpression *> funcList,
			     functionExpression * newFunction);

// make floor,ceil,round type Expression and return it.
Expression * makeSingleExpr(std::string op, Expression * the) {
  if (op == "floor")
    return new floorFunction(the);
  else if (op == "ceil")
    return new ceilFunction(the);
  else { //round
    return new roundFunction(the);
  }
}

// make +,-,*,/,%,^ and return it.
Expression * makeExpr(std::string op, Expression * lhs, Expression * rhs) {
  if (op == "+")
    return new PlusExpression(lhs, rhs);
  else if (op == "-")
    return new MinusExpression(lhs, rhs);
  else if (op == "*")
    return new TimesExpression(lhs, rhs);
  else if (op == "/")
    return new DivExpression(lhs, rhs);
  else if (op == "%")
    return new ModExpression(lhs, rhs);
  else if (op == "^")
    return new PowExpression(lhs, rhs);
  else //logb
    return new LogbExpression(lhs, rhs);
}

// given a string, ensure it is one of the +,-,*,/,%,^
bool isValidOp(const string & op) {
  if( (strchr("+-*/%^", op[0])) && (op.length() == 1) ) {
    return true;
  }
  if(op == "logb") {
    return true;
  }
  return false;
}

//given the string ensure it is one of "floor", "ceil" or "round"
bool isValidSingleOp(const string & op) {
  if( (op == "floor") ||
      (op == "ceil") ||
      (op == "round")
      ) {
    return true;
  }
  return false;
}

// check whether the first operator in inputString is recognizable. created correspoding expression and return it.
// Input: fname expr ....)
// Output: Corresponding a pointer to a expression
Expression * parseOp(string & inputString,
		     map<string, functionExpression *> funcList,
		     functionExpression * newfunction) {
  StringSkipSpace(inputString);
  int oplength = FindWordLength(inputString);
  if(oplength == 0) {
    cerr << "lack Op" << endl;
    return NULL;
  }
  string op = inputString.substr(0,oplength);
  if (isValidOp(op)) { //+ - * / % ^ logb
    inputString = inputString.substr(oplength);
    Expression * lhs = ParseExpression(inputString, funcList, newfunction);
    if (lhs == NULL) {
      return NULL;
    }
    Expression * rhs = ParseExpression(inputString, funcList, newfunction);
    if (rhs == NULL) {
      if(!::isDelete.count(lhs) ) {
	delete lhs;
      }
      return NULL;
    }
    StringSkipSpace(inputString);
    if(inputString[0] != ')') {
      if(!::isDelete.count(lhs) ) {
	delete lhs;
      }
      if(!::isDelete.count(rhs) ) {
	delete rhs;
      }
      cerr << "lack )" << endl;
      return NULL;
    }
    inputString = inputString.substr(1);
    return makeExpr(op, lhs, rhs);
  }
  else if (isValidSingleOp(op)) { //floor ceil round
    inputString = inputString.substr(oplength);
    Expression * the = ParseExpression(inputString, funcList, newfunction);
    if ( the == NULL ) {
      return NULL;
    }
    StringSkipSpace(inputString);
    if(inputString[0] != ')') {
      if(!::isDelete.count(the) ) {
	delete the;
      }
      cerr << "lack )" << endl;
      return NULL;
    }
    inputString = inputString.substr(1);
    return makeSingleExpr(op, the);
  }
  else if (op == "select") {
    inputString = inputString.substr(oplength);
    Expression * lhs = ParseExpression(inputString, funcList, newfunction);
    if (lhs == NULL) {
      return NULL;
    }
    Expression * mhs = ParseExpression(inputString, funcList, newfunction);
    if (mhs == NULL) {
      if(!::isDelete.count(lhs) ) {
	delete lhs;
      }
      return NULL;
    }
    Expression * rhs = ParseExpression(inputString, funcList, newfunction);
    if (rhs == NULL) {
      if(!::isDelete.count(lhs) ) {
	delete lhs;
      }
      if(!::isDelete.count(mhs) ) {
	delete mhs;
      }
      return NULL;
    }
    StringSkipSpace(inputString);
    if(inputString[0] != ')') {
      if(!::isDelete.count(lhs) ) {
	delete lhs;
      }
      if(!::isDelete.count(mhs) ) {
	delete mhs;
      }
      if(!::isDelete.count(rhs) ) {
	delete rhs;
      }
      cerr << "lack )" << endl;
      return NULL;
    }
    inputString = inputString.substr(1);
    return new SelectExpression(lhs, mhs, rhs);
  }
  // user defined function
  else if (funcList.find(op) != funcList.end()) {//user-defined function
    inputString = inputString.substr(oplength);
    vector<parameterExpression *> parameters = funcList[op]->getParas();
    for(auto it = parameters.begin(); it != parameters.end(); ++it) {
      StringSkipSpace(inputString);
      Expression * tempExpression = ParseExpression(inputString, funcList, newfunction);
      (*it)->setMaterial(tempExpression);
    }
    StringSkipSpace(inputString);
    if(inputString[0] != ')') {
      cerr << "lack )" << endl;
      return NULL;
    }
    inputString = inputString.substr(1);
    return funcList[op];
  }
  cerr << "Invalid op: " << op << endl;
  return NULL;
}

// parse string, ditinguish function-like expression (f 2 3) and ordinary expression ex:number or parameter
// Input : expr

Expression * ParseExpression(string & inputString,
		map<string, functionExpression *> funcList,
		functionExpression * newfunction) {
  StringSkipSpace(inputString);
  if( inputString[0] == '\0' ) {
    cerr << "lack expression" << endl;
    return NULL;
  }
  else if (inputString[0] == '(') {
    inputString.erase(0,1);
    return parseOp(inputString, funcList, newfunction);
  }
  else {
    //number or parameterExpression
    int length = FindWordLength(inputString);
    string numOrparameter = inputString.substr(0,length);
    inputString = inputString.substr(length);
    char * ruler;
    double number = strtod(numOrparameter.c_str(), &ruler);
    if( numOrparameter.length() == (size_t)(ruler - &(numOrparameter.c_str()[0])) ){//number
      return new numericExpression(number);
    }
    else {//parameter
      string name = numOrparameter;
      vector<parameterExpression *> paras = newfunction->getParas();
      for(auto it = paras.begin(); it != paras.end(); ++it) {
	if(name == (*it)->getParaName()) {
	  return *it;
	}
      }
      //no match parameter
      cerr << "No this parameter " << name << endl;
      return NULL;
    }
  }
}


//after "define" command, define a function
//Input : define (id id ...) = (fname expr ....)
void DefineFunction(string inputString,
                                    map<string, functionExpression *> & funcList) {
  inputString = inputString.substr(6);
  StringSkipSpace(inputString);
  if(inputString[0] != '(') {
    cout << "except ( but find " << inputString[0] << endl;
    throw exception();
  }
  inputString.erase(0, 1);
  StringSkipSpace(inputString);
  // get function name
  int namelength = FindWordLength(inputString);
  if( namelength == 0 ) {
    cout << "lack of function name" << endl;
    throw exception();
  }
  string fname = inputString.substr(0,namelength);
  if(funcList.find(fname) != funcList.end()) {
    cerr << "you have already define function: " << fname << endl;
    throw exception();
  }
  inputString = inputString.substr(namelength);
  // get parameter id
  vector<string> parametername;
  int num_of_para = 0;
  do{
    StringSkipSpace(inputString);
    int paralength = FindWordLength(inputString);
    if( paralength == 0 ) {
      break;
    }
    parametername.push_back( inputString.substr(0,paralength) );
    inputString = inputString.substr(paralength);
    num_of_para++;
  } while(1);
  if(num_of_para == 0) {
    cout << "lack of parameter" << endl;
    throw exception();
  }
  if(inputString[0] != ')') {
    cout << "excepted ) but find " << inputString[0] << endl;
    throw exception();
  }
  inputString.erase(0, 1);
  StringSkipSpace(inputString);
  if(inputString[0] != '=') {
    cout << "excepted = but find " << inputString[0] << endl;
    throw exception();
  }
  inputString = inputString.erase(0, 1);
  vector<parameterExpression *> parameters;
  for (int j = 0; j < num_of_para; j++) {
    parameterExpression * tmp = new parameterExpression(parametername[j], NULL);
    parameters.push_back(tmp);  // creat parameters' expression
    ::isDelete.insert(tmp);
  }
  functionExpression * newFunction =
      new functionExpression(fname, parameters, NULL);  // creat function expression
  ::isDelete.insert(newFunction);
  Expression * expr = ParseExpression(inputString, funcList, newFunction);  //parse the expression
  if(expr == NULL) {
    delete newFunction;
    throw exception();
  }
  newFunction->setFunctionExpression(expr);
  funcList[newFunction->getName()] = newFunction;
  cout << "defined " << newFunction->getName() << "(";
  parameters = newFunction->getParas();
  ::isDelete.insert(parameters[0]);
  cout << parameters[0]->getParaName();
  for(auto it = parameters.begin()+1; it != parameters.end(); ++it) {
    ::isDelete.insert(*it);
    cout << " "<< (*it)->getParaName();
  }
  cout << ")" << endl;;
}

// change "(fname expr ...)" to "fname(expr ...)"
string ReconstructExpre(string inputString) {
  stack<char> myStack;  //using stack to find the length of an whole expression
  StringSkipSpace(inputString);
  myStack.push(inputString[0]);
  size_t i = 1;
  while (1) {
    if (i == inputString.size()) {
      std::cerr << "lack )" << endl;
      throw exception();
    }
    if (inputString[i] == '(') {
      myStack.push('(');
    }
    else if (inputString[i] == ')') {
      myStack.pop();
    }
    if (myStack.empty()) {
      break;
    }
    ++i;
  }  // i is the length of this whole expression
  string functionInput = inputString.substr(1, i-1);
  StringSkipSpace(functionInput);
  return functionInput;
}

//after test command, test the answer and expected result
//Input : "test (fname expr) expr"
void checkAnswer(string inputString,
                 map<std::string, functionExpression *> & allFunctions) {
  inputString = inputString.substr(4);
  StringSkipSpace(inputString);
  if(inputString[0] != '(') {
    cout << "except ( but find " << inputString[0] << endl;
    throw exception();
  }
  string functionInput = ReconstructExpre(inputString);
  int length = FindWordLength(functionInput);
  string fname = functionInput.substr(0,length);
  functionInput.erase(0, length);
  StringSkipSpace(functionInput);
  
  Expression * ans = ParseExpression(inputString, allFunctions, NULL);
  if(ans == NULL) {
    throw exception();
  }
  double answer = ans->evaluate();
  StringSkipSpace(inputString);
  Expression * expected = ParseExpression(inputString, allFunctions, NULL);
  if(expected == NULL) {
    throw exception();
  }
  double expected_num = expected->evaluate();
  bool equal = (fabs(expected_num - answer) < 0.0000000001);
  if(equal) {
    cout  << fname << "(" << functionInput << ") = " << answer << " [correct]" << endl;
  }
  else {
    cout  << fname << "(" << functionInput << ") = " << answer << " [INCORRECT expected: " << expected_num << "]" << endl;
  }
  if(!::isDelete.count(expected) ) {
    delete expected;
  }
}

// delete all the element after the pound-sign
void passPound(string & inputString) {
  if( inputString.find_first_of("#") != string::npos ) {
    inputString.erase(inputString.find_first_of("#"));
    cout << "size: " << inputString.length() << endl;
  }
}


int main(void) {
  map<std::string, functionExpression *> allFunctions;

  char * line = NULL;
  size_t sz;
  while (getline(&line, &sz, stdin) != -1) {  //read the instructions and do the work
    string inputString = line;
    passPound(inputString);
    StringSkipSpace(inputString);
    try{
	if(inputString.substr(0, 6) == "define") {  
	  DefineFunction(inputString, allFunctions);
	}
	else if(inputString.substr(0, 4) == "test") {
	  checkAnswer(inputString, allFunctions);
	}
	else if (inputString.substr(0, 4) == "exit"){
	    break;
	}
	else {
	  cerr << "plz use keyword: define or test" << endl;
	}
      }
    catch(exception & e) {
      e.what();
    }
  }
  
  for(auto it = allFunctions.begin(); it != allFunctions.end(); ++it) {
    delete it->second;
  }
  free(line);
  
  return EXIT_SUCCESS;
}
