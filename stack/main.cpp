#include <iostream>
//#include "stack.h"
#include "rstack.h"

using Stack = ResizingStack;

void testStack() {
  Stack s;
  std::cout << "s.empty() == " << s.empty() << std::endl;
  s.push(42);
  std::cout << "s.empty() == " << s.empty() << std::endl;
  std::cout << "s.peek() == " << s.peek() << std::endl;
  std::cout << "s.pop() == " << s.pop() << std::endl;
  std::cout << "s.empty() == " << s.empty() << std::endl;
  for(int i = 0; i < 10; i++)
    s.push(i);
  while(!s.empty())
    std::cout << "s.pop() == " << s.pop() << std::endl;
}

char printDigit(int d) {
  if (d < 10)
    return d + '0';
  return (d - 10) + 'A';
}

// извежда n в k-ична бройна система
void printInBase(int n, int k) {
  Stack s;
  std::cout << n << "(10) --> ";
  while (n > 0) {
    s.push(n % k);
    n /= k;
  }
  // n == 0
  while (!s.empty())
    std::cout << printDigit(s.pop());
  std::cout << "(" << k << ")\n";
}

void testPrintInBase() {
  printInBase(12, 2);
  printInBase(255, 2);
  printInBase(1140, 6);
  printInBase(6936, 31);
}


bool isdigit(char c) {
  return '0' <= c && c <= '9';
}

bool isop(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '=';
}

int calculate(int arg1, char op, int arg2) {
  switch(op) {
  case '+': return arg1 + arg2;
  case '-': return arg1 - arg2;
  case '*': return arg1 * arg2;
  case '/': return arg1 / arg2;
  case '%': return arg1 % arg2;
  }
  return 0;
}

int todigit(char c) {
  return c - '0';
}

/*
   <израз> ::= <цифра> | (<израз><операция><израз>)
   функцията ще пресмята израза започващ от s
   и ще премества s след края на израза
*/

int calculate_expr(char const* s) {
  Stack args;
  Stack ops;
  while(*s) {
    // magic
    if (isdigit(*s))
      args.push(todigit(*s));
    else if (isop(*s))
      ops.push(*s);
    else if (*s == ')') {
      int rarg = args.pop(), larg = args.pop();
      char op = ops.pop();
      args.push(calculate(larg, op, rarg));
    }
    s++;
  }
  return args.pop();
}

const int MAXEXPR = 101;

void testExpression() {
  char expr[MAXEXPR] = "";
  std::cout << "Въведете израз: ";
  std::cin.getline(expr, MAXEXPR);
  char const *s = expr;
  std::cout << "Резултатът е: " << calculate_expr(s) << std::endl;  
}

bool isOpenParenthesis(char c) {
  return c == '(' || c == '[' || c == '{';
}

bool isCloseParenthesis(char c) {
  return c == ')' || c == ']' || c == '}';
}

bool matchParentheses(char open, char close) {
  return
    (open == '(' && close == ')') ||
    (open == '[' && close == ']') ||
    (open == '{' && close == '}');
}

bool checkParentheses(char const* expr) {
  Stack pstack;
  while(*expr) {
    if (isOpenParenthesis(*expr))
      pstack.push(*expr);
    else
      if (isCloseParenthesis(*expr))
        if (pstack.empty() ||  // повече затварящи
            !matchParentheses(pstack.pop(), *expr)) // несъвпадащи скоби
          return false;
    expr++;
  }
  return pstack.empty(); // повече отварящи
}

void testParenthesesExpression(char const* expr, bool expectedResult) {
  bool result = checkParentheses(expr);
  std::cout << "[";
  if (result == expectedResult)
    std::cout << "OK";
  else
    std::cout << "ERROR!";
  std::cout << "] ";
  std::cout << "checkParentheses(" << expr << ") = " << result << std::endl;
}

void testParentheses() {
  std::cout << "------------------------------\n";
  testParenthesesExpression("(2+3)", true);
  testParenthesesExpression("((2+3)", false);
  testParenthesesExpression("(2+3))", false);
  testParenthesesExpression("(2+3]", false);
  testParenthesesExpression("(2+(3+(4+5)))", true);
  testParenthesesExpression("(((2+3)+4)+5)", true);
  testParenthesesExpression("{2+[(3-4)+5]}", true);
  testParenthesesExpression("{2+[(3-4)+5}]", false);
  testParenthesesExpression("", true);
  testParenthesesExpression("(", false);
  testParenthesesExpression("}", false);
  testParenthesesExpression("32408923408732487+239847", true);
  testParenthesesExpression("(((((([[[{{[[[[{[{", false);
  testParenthesesExpression(")))]]]}}}))", false);
  testParenthesesExpression(")2(", false);
  testParenthesesExpression("(+)", true);
  testParenthesesExpression("(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((())))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))", true);
  std::cout << "------------------------------\n\n\n";
}

int main() {
  // testStack();
  // testPrintInBase();
  // testExpression();
  testParentheses();
  return 0;
}