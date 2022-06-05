#include <exception>

#include "utils.hpp"
#include "StackArray.hpp"

const int getSizeOfCString(const char* text)
{
  int i = 0;
  while (text[i] != '\0')
  {
    i++;
  }
  
  return i;
}

int getPriority(const char& element)
{
  switch (element)
  {
  case ('('):
    return 0;

  case (')'):
    return 1;

  case ('+'):
  case ('-'):
    return 2;

  case ('*'):
  case ('/'):
    return 3;

  default:
    return -1;
  }
}


bool checkBalanceBrackets(const char* text, const int& maxDeep)
{
  StackArray< char > brackets(maxDeep);

  const int textSize = getSizeOfCString(text);

  for (size_t i = 0; i < textSize; i++)
  {
    if (text[i] == '(' || text[i] == '[' || text[i] == '{')
    {
      brackets.push(text[i]);
    }
    else if (text[i] == ')')
    {
      if (int(brackets.pop()) != 40)
      {
        return false;
      }
    }
    else if (text[i] == ']')
    {
      if (int(brackets.pop()) != 91)
      {
        return false;
      }
    }
    else if (text[i] == '}')
    {
      if (int(brackets.pop()) != 123)
      {
        return false;
      }
    }
  }

  if (brackets.isEmpty() == false)
  {
    return false;
  }

  return true;
}

bool getPostfixFromInfix(const char* infix, char* postfix, const size_t& stackSize)
{
  StackArray< char > operators(stackSize);
  const int infixSize = getSizeOfCString(infix);

  if (infixSize <= 2)
  {
    throw std::logic_error("There is no expression\n");
  }

  if (checkBalanceBrackets(infix, infixSize) == false)
  {
    throw std::logic_error("Bad brackets\n");
  }

  char popedElement;
  size_t k = 0; //Index for postfix
  for (size_t i = 0; i < infixSize; i++)
  {
    if (infix[i] == '[' || infix[i] == '{' || infix[i] == ']' || infix[i] == '}')
    {
      throw std::logic_error("Allowed only '(' and ')'\n");
    }

    if (infix[i] == '(')
    {
      operators.push(infix[i]);
    }
    else if (infix[i] >= '1' && infix[i] <= '9')
    {
      postfix[k++] = infix[i];
    }
    else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/')
    {
      if (operators.isEmpty())
      {
        operators.push(infix[i]);
      }
      else
      {
        do
        {
          popedElement = operators.pop();
          if (getPriority(popedElement) >= getPriority(infix[i]))
          {
            postfix[k++] = popedElement;
          }
          else
          {
            operators.push(popedElement);
            break;
          }
        } while (operators.isEmpty() == false);
        operators.push(infix[i]);
      }
    }
    else if (infix[i] == ')')
    {
      popedElement = operators.pop();
      while (popedElement != '(')
      {
        postfix[k++] = popedElement;
        popedElement = operators.pop();
      }
    }
    else
    {
      throw std::logic_error("Bad expression\n");
    }
  }

  while (operators.isEmpty() == false)
  {
    postfix[k++] = operators.pop();
  }
  postfix[k] = '\0';

  return true;
}

int evaluatePostfix(const char* postfix, const size_t& stackSize)
{
  StackArray< char > numbers(stackSize);
  size_t postfixSize = getSizeOfCString(postfix);

  if (postfixSize <= 2)
  {
    throw std::logic_error("There is no expression\n");
  }

  int first = 0;
  int second = 0;
  int count = 0;
  for (size_t i = 0; i < postfixSize; i++)
  {
    if (postfix[i] >= '1' && postfix[i] <= '9')
    {
      numbers.push(int(postfix[i]) - 48);
      if (count != 2)
      {
        ++count;
      }
      else
      {
        count = 1;
      }
    }
    else if (postfix[i] == '+')
    {
      first = numbers.pop();
      second = numbers.pop();
      numbers.push(second + first);
    }
    else if (postfix[i] == '-')
    {
      if (count != 1)
      {
        first = numbers.pop();
        second = numbers.pop();
        numbers.push(second - first);
      }
      else
      {
        first = numbers.pop();
        numbers.push(-first);
      }
    }
    else if (postfix[i] == '*')
    {
      first = numbers.pop();
      second = numbers.pop();
      numbers.push(second * first);
    }
    else if (postfix[i] == '/')
    {
      first = numbers.pop();
      second = numbers.pop();
      numbers.push(second / first);
    }
    else
    {
      throw std::logic_error("Bad postfix expression\n");
    }
  }

  return numbers.pop();
}
