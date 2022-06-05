#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

const int getSizeOfCString(const char* text);
int getPriority(const char& element);
bool checkBalanceBrackets(const char* text, const int& maxDeep);
bool getPostfixFromInfix(const char* infix, char* postfix, const size_t& stackSize);
int evaluatePostfix(const char* postfix, const size_t& stackSize);

#endif
