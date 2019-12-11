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

// input: a vector of parameter
// output: check whether those parameters are unique, and return true or false
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
      if(tempExpression == NULL) {
	return NULL;
      }
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
  if( inputString[0] == '\0' || inputString[0] == ')' ) {
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
  //check whether parameter is unique
  if( !IsUniquePara(parametername) ) {
    cerr << "your input parameter is not unique" << endl;
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

void skipSpace(const char ** strp) {
  while(isspace(**strp)) {
    *strp = *strp + 1;
  }
}

//input: numerical parameter in char** form
//seperate the parameters into a vector of parameters
void scanparameter(const char ** in, vector<double> & parameter) {
  char * next;
  do {
    double tmp = strtod(*in, &next);
    //cout << tmp << " ";
    if (next == *in) {
      std::cerr << "Expected a number, but found " << **in << "\n";
      throw exception();
    }
    parameter.push_back(tmp);
    *in = next;
    skipSpace(in);
  } while(**in != '\0');
}


bool lessthan(double a, double b) {
  a += 0.00000000001;
  if(a < b) {
    return true;
  }
  return false;
}

//given the function name, step size, ranges of each parameter.
//The functino print out the numerical integration
void Numint(string inputString,
                 map<std::string, functionExpression *> & allFunctions) {
  inputString = inputString.substr(6);
  StringSkipSpace(inputString);
  int length = FindWordLength(inputString);
  string fname = inputString.substr(0,length);
  if (allFunctions.find(fname) == allFunctions.end()) {
    cerr << "YOU DO NOT DEFINE THIS FUNCTION: " << fname << endl;
    throw exception();
  }
  inputString = inputString.substr(length);
  functionExpression * func = allFunctions[fname];
  const char * inputChar = inputString.c_str();
  vector<double> parameter;
  scanparameter(&inputChar, parameter);
  size_t dimension = func->getLength();
  if( parameter.size() != dimension * 2 + 1) {
    cerr << "YOU PARAMETERS NUMBER IS NOT MATCH" << endl;
    throw exception();
  }

  double sum = 0;
  double width = parameter[0];
  vector<double> vec1;
  vector<double> vec2;
  int total_point = 1;
  //vec1 record the lower range. vec2 record the upper range
  for(size_t i = 0; i < dimension; i++) {
    vec1.push_back(parameter[2*i+1]);
    vec2.push_back(parameter[2*i+2]);
    if(vec2[i] <= vec1[i]) {
      cerr << "For each Parameter, you should write lower limit first and upper limit later" << endl;
      throw exception();
    }
    total_point *= (vec2[i] - vec1[i])/width;
  }
  bool show_process = false;
  if(total_point > 100000) {
    cout << "There will be approximately " << total_point << " points to calculate" << endl;
    show_process = true;
  }
  total_point = total_point/10;
  int process = 0;
  vector<double> vec1_cp = vec1;
  while(1) {
    if(show_process && process % total_point == 0) { 
      cout << 10 * process/total_point << "% of work have been processed. plz wait" << endl;
    }
    double delta = 0;
    vector<double> vec3 = vec1;
    //The first while loop is to calculate the small area of one point
    //vec3 record the base points, and vec1 calculate the surrounding points
    //for example, vec3 is (x,y) and vec1 will be (x,y) (x+width,y) (x,y+width) (x+width,y+width) throught the for loop
    while(1) {
      delta += func->evaluateFromNumPara(vec1);
      vec1[0] += width;
      for(size_t j = 0; j < dimension - 1; j++) {
	if( lessthan( vec3[j] + width, vec1[j] ) ) {
	  vec1[j] = vec3[j];
	  vec1[j+1] +=  width;
	}
      }
      if( lessthan(vec3[dimension - 1]+width, vec1[dimension - 1] ) ){
	vec1 = vec3;
	break;
      }
    }
    sum = sum + delta / pow(2/width, dimension);
    vec1[0] = vec1[0] + width;
    //vec2 is used to recorded the upper range
    for(size_t i = 0; i < dimension - 1; i++) {
      if(vec1[i] > vec2[i] - width) {
	vec1[i] = vec1_cp[i];
	vec1[i+1] = vec1[i+1] + width;
      }
    }
    if(vec1[dimension - 1] > vec2[dimension - 1]- width) {
      break;
    }
    process++;
  }
  cout << "numerical intergration: " << sum << endl;
}

  
  


//output a random number between fMin and fMax
double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

//given the function, number of trails and ranges of each parameters
//print out the monte carlo result of function integration
void mcint(string inputString,
                 map<std::string, functionExpression *> & allFunctions) {
  inputString = inputString.substr(5);
  StringSkipSpace(inputString);
  int length = FindWordLength(inputString);
  string fname = inputString.substr(0,length);
  if (allFunctions.find(fname) == allFunctions.end()) {
    cerr << "YOU DO NOT DEFINE THIS FUNCTION: " << fname << endl;
    throw exception();
  }
  inputString = inputString.substr(length);
  functionExpression * func = allFunctions[fname];
  const char * inputChar = inputString.c_str();
  vector<double> parameter;
  scanparameter(&inputChar, parameter);
  size_t dimension = func->getLength();
  if( parameter.size() != dimension * 2 + 1) {
    cerr << "YOU PARAMETERS NUMBER IS NOT MATCH" << endl;
    throw exception();
  }
  //vec1 is lower limit, vec2 is upper limit
  //a random vector will be created and stored in vec3
  double sum = 0;
  size_t trials = (size_t)parameter[0];
  vector<double> vec1;
  vector<double> vec2;
  vector<double> vec3(dimension, 0);
  for(size_t i = 0; i < dimension; i++) {
    vec1.push_back(parameter[2*i+1]);
    vec2.push_back(parameter[2*i+2]);
  }
  for(size_t i = 0; i < trials; i++) {
    for(size_t j = 0; j < dimension; j++) {
      vec3[j] = fRand(vec1[j], vec2[j]);
    }
    sum += func->evaluateFromNumPara(vec3);
  }
  double integrate = sum/trials;
  for(size_t j = 0; j < dimension; j++) {
    integrate = integrate * (vec2[j]- vec1[j]);
  }
  cout << "Monte Carlo simulation result: " << integrate << endl;
}

//given two vector(can be considered as two points)
//calculate the distnce between two point
double dist(vector<double> & a, vector<double> & b) {
  if(a.size() != b.size()) {
    cout << "a and b is not match" << endl;
    throw exception();
  }
  double sum = 0;
  for(size_t i = 0; i < a.size(); i++) {
    sum += pow(a[i]-b[i], 2);
  }
  return sqrt(sum);
}

//print all element in the vector
//by seperating them between comma and adding parenthesis
template <typename type>
void SeperateInParenthesis(vector<type> & a) {
  cout << "(" << a[0];
  for(auto it = a.begin()+1; it != a.end(); ++it) {
    cout << "," << *it;
  }
  cout << ")";
}

//given the function name, gamma, convergeDistance, maximum number of steps, starting point in "inputString"
//calculate the local maximum(minimum) of the function
//input: f is function "add" or "reduce", which decide whether it is "max" or "min"
void grandient(string inputString,
	       map<std::string, functionExpression *> & allFunctions, double (*f)(double, double)) {
  inputString = inputString.substr(3);
  StringSkipSpace(inputString);
  int length = FindWordLength(inputString);
  string fname = inputString.substr(0,length);
  if (allFunctions.find(fname) == allFunctions.end()) {
    cerr << "YOU DO NOT DEFINE THIS FUNCTION: " << fname << endl;
    throw exception();
  }
  inputString = inputString.substr(length);
  functionExpression * func = allFunctions[fname];
  const char * inputChar = inputString.c_str();
  vector<double> parameter;
  scanparameter(&inputChar, parameter);
  size_t dimension = func->getLength();
  if( parameter.size() != dimension + 3) {
    cerr << "YOU PARAMETERS NUMBER IS NOT MATCH" << endl;
    throw exception();
  }
  double gamma = parameter[0];
  double convergeddist = parameter[1];
  double delta = convergeddist;
  if(gamma < 0 || convergeddist < 0 || parameter[2] < 1) {
    cerr << "gamma, converged distance, and num of trails should be positive, plz try again" << endl;
    throw exception();
  }
  size_t max_iteration = (size_t)parameter[2];
  vector<double> set(parameter.begin() + 3, parameter.end());
  double old_value;
  while(1) {
    max_iteration--;
    old_value = func->evaluateFromNumPara(set);
    vector<double> new_set;
    set[0] += delta;
    double accend = (func->evaluateFromNumPara(set)-old_value) / delta *gamma;
    new_set.push_back( f(set[0], accend) - delta );
    for(size_t i = 1; i < dimension; i++) {
      set[i] += delta;
      set[i-1] -= delta;
      double accend = (func->evaluateFromNumPara(set)-old_value) / delta *gamma;
      new_set.push_back( f(set[i], accend) - delta );
    }
    set[dimension-1] -= delta;
    if(dist(set, new_set) < convergeddist ||
       max_iteration == 0) {
      break;
    }
    set.swap(new_set);
  }
  if(max_iteration == 0) {
    cout << "Do not converged but current ";
  }
  //create a vector named "parameter_str", which contain all the id of parameter.
  vector<string> parameter_str;
  vector<parameterExpression *> expr = func->getParas();
  for(auto it = expr.begin(); it != expr.end(); ++it) {
    parameter_str.push_back((*it)->getParaName());
  }
  cout << "Local maximun(minumum) is " << old_value << " when ";
  SeperateInParenthesis<string>(parameter_str);
  cout << " = ";
  SeperateInParenthesis<double>(set);
  cout << endl;
  return;
}

double add(double a, double b) {
  return a+b;
}

double reduce(double a, double b) {
  return a-b;
}

void max(string inputString,
	 map<std::string, functionExpression *> & allFunctions) {
  cout << "MAX: ";
  grandient(inputString, allFunctions, add);
}

void min(string inputString,
	 map<std::string, functionExpression *> & allFunctions) {
  cout << "MIN: ";
  grandient(inputString,allFunctions, reduce);
}

// delete all the element after the pound-sign
void passPound(string & inputString) {
  if( inputString.find_first_of("#") != string::npos ) {
    inputString.erase(inputString.find_first_of("#"));
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
	else if(inputString.substr(0, 6) == "numint") {
	  Numint(inputString, allFunctions);
	}
	else if(inputString.substr(0, 5) == "mcint") {
	  mcint(inputString, allFunctions);
	}
	else if(inputString.substr(0, 3) == "max") {
	  max(inputString, allFunctions);
	}
	else if(inputString.substr(0, 3) == "min") {
	  min(inputString, allFunctions);
	}
	else if (inputString.substr(0, 4) == "exit"){
	    break;
	}
	else {
	  cerr << "plz use keyword: define, test, numint, mcint, max, min" << endl;
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
