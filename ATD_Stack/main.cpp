#include <iostream>

#include "StackArray.hpp"
#include "utils.hpp"

int main()
{
  const char* InfixExp = "(1+2-(3+4))*(5-1)/(-2)";
  std::cout << "Infix expression is " << InfixExp << "\n";
  const int InfixExpSize = getSizeOfCString(InfixExp);
  char* PostfixExp = new char[InfixExpSize];
  try
  {
    getPostfixFromInfix(InfixExp, PostfixExp, 4);
    std::cout << "\nPostfix expression is " << PostfixExp << "\n";
    std::cout << "\nThis expression equals to " << evaluatePostfix(PostfixExp, 3) << "\n";
  }
  catch (const StackArray< char >::StackException& exc)
  {
    std::cerr << exc.getMessage();
  }
  catch (const std::exception& exc)
  {
    std::cerr << exc.what();
  }

  return 0;
}
