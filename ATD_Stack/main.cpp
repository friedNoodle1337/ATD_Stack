#include <iostream>

#include "StackArray.hpp"

int main()
{
  try
  {
    StackArray< char > myStack(-1);
    std::cout << myStack << "\n";
  }
  catch (const StackArray< char >::StackException& exc)
  {
    std::cerr << exc.getMessage();
  }

  return 0;
}
