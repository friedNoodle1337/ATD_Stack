#ifndef STACKARRAY_HPP
#define STACKARRAY_HPP

#include <iostream>
#include <string>
#include <limits>

#include "ATDStack.hpp"

template < class T >
class StackArray: public Stack< T >
{
public:
  StackArray(size_t size = 100);
  StackArray(const StackArray< T >& src) = delete;
  StackArray(StackArray< T >&& src);
  virtual ~StackArray() { delete[] array_; }

  StackArray& operator=(const StackArray< T >& src) = delete;
  StackArray& operator=(StackArray< T >&& src);
  //T& operator[](const int& index);
  template < class T1 >
  friend std::ostream& operator<<(std::ostream& out, StackArray< T1 >& src);

  void push(const T& e) override;
  T pop() override;
  bool isEmpty() override;

  class StackException
  {
  public:
    StackException(const std::string message): message_(message) {}
    virtual const std::string getMessage() const = 0;

  private:
    std::string message_;
  };

private:
  T* array_ = nullptr;
  size_t top_;
  size_t size_;
  void swap(StackArray< T >& src);
};

template < class T >
class StackOverflow: public StackArray< T >::StackException
{
public:
  StackOverflow(const std::string message = "Stack Overflow"): StackException(message), message_(message) {}
  const std::string getMessage() const override { return message_; }

private:
  std::string message_;
};

template < class T >
class StackUnderflow: public StackArray< T >::StackException
{
public:
  StackUnderflow(const std::string message = "Stack Underflow"): StackException(message), message_(message) {}
  const std::string getMessage() const override { return message_; }

private:
  std::string message_;
};

template < class T >
class WrongStackSize: public StackArray< T >::StackException
{
public:
  WrongStackSize(const std::string message = "Wrong Stack Size"): StackException(message), message_(message) {}
  const std::string getMessage() const override { return message_; }

private:
  std::string message_;
};

template < class T >
StackArray< T >::StackArray(size_t size):
  top_(0)
{
  if (size >= std::numeric_limits< size_t >::min() && size < std::numeric_limits< size_t >::max())
  {
    size_ = size;
    array_ = new T[size + 1];
  }
  else
  {
    throw WrongStackSize< T >();
  }
}

template < class T >
StackArray< T >::StackArray(StackArray< T >&& src):
  array_(src.array_),
  top_(src.top_),
  size_(src.size_)
{
  if (this != src)
  {
    swap(src);
  }
}

template < class T >
StackArray< T >& StackArray< T >::operator=(StackArray< T >&& src)
{
  if (this != src)
  {
    swap(src);

    src.array_ = nullptr;
    src.top_ = nullptr;
    src.size_ = nullptr;
  }
  
  return *this;
}

//template < class T >
//T& StackArray< T >::operator[](const int& index)
//{
//  return array_[index];
//}

template < class T1 >
std::ostream& operator<<(std::ostream& out, StackArray< T1 >& src)
{
  if (!(src.isEmpty()))
  {
    for (int i = 1; i <= src.top_; ++i)
    {
      out << src.array_[i] << " ";
    }
  }
  else
  {
    out << "Stack is empty";
  }

  return out;
}

template < class T >
void StackArray< T >::push(const T& e)
{
  if (top_ == size_)
  {
    throw StackOverflow< T >();
  }
  array_[++top_] = e;
}

template < class T >
T StackArray< T >::pop()
{
  if (isEmpty())
  {
    throw StackUnderflow< T >();
  }
  return array_[top_--];
}

template < class T >
bool StackArray< T >::isEmpty()
{
  return top_ == 0;
}

template < class T >
void StackArray< T >::swap(StackArray< T >& src)
{
  std::swap(array_, src.array_);
  std::swap(top_, src.top_);
  std::swap(size_, src.size_);
}

#endif
