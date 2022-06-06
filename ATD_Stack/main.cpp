#include <iostream>

#include "StackArray.hpp"
#include "utils.hpp"

int main()
{
  //const char* InfixExp = "(1+2-(3+4))*(5-1)/(-2)";
  //const int InfixExpSize = getSizeOfCString(InfixExp);
  //char* PostfixExp = new char[InfixExpSize];
  //try
  //{
  //  getPostfixFromInfix(InfixExp, PostfixExp, 12);
  //  std::cout << evaluatePostfix(PostfixExp, 12) << "\n";
  //}
  //catch (const StackArray< char >::StackException& exc)
  //{
  //  std::cerr << exc.getMessage();
  //}
  //catch (const std::exception& exc)
  //{
  //  std::cerr << exc.what();
  //}

  StackArray< char > stack;
  stack.push('a');
  stack.push('b');
  stack.push('c');
  stack.push('d');
  std::cout << stack << "\n";

  return 0;
}
