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
  StackArray(const StackArray< T >& other) = delete;
  StackArray(StackArray< T >&& other);
  virtual ~StackArray() { delete[] array_; }

  StackArray& operator=(const StackArray< T >& other) = delete;
  StackArray& operator=(StackArray< T >&& other);
  template < class T1 >
  friend std::ostream& operator<<(std::ostream& out, StackArray< T1 >& other);

  void push(const T& e) override;
  T pop() override;
  bool isEmpty() const override;

  class StackException
  {
  public:
    StackException(const std::string message): message_(message) {}
    virtual const std::string getMessage() const { return message_; }

  private:
    std::string message_;
  };

private:
  T* array_ = nullptr;
  size_t top_;
  size_t size_;
  void swap(StackArray< T >& other);
};

template < class T >
class StackOverflow: public StackArray< T >::StackException
{
public:
  StackOverflow(const std::string message = "Stack Overflow"): StackException(message) {}
};

template < class T >
class StackUnderflow: public StackArray< T >::StackException
{
public:
  StackUnderflow(const std::string message = "Stack Underflow"): StackException(message) {}
};

template < class T >
class WrongStackSize: public StackArray< T >::StackException
{
public:
  WrongStackSize(const std::string message = "Wrong Stack Size"): StackException(message) {}
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
StackArray< T >::StackArray(StackArray< T >&& other):
  array_(other.array_),
  top_(other.top_),
  size_(other.size_)
{
  other.array_ = nullptr;
  other.top_ = nullptr;
  other.size_ = nullptr;
}

template < class T >
StackArray< T >& StackArray< T >::operator=(StackArray< T >&& other)
{
  if (this != &other)
  {
    swap(other);
  }
  
  return *this;
}

template < class T1 >
std::ostream& operator<<(std::ostream& out, StackArray< T1 >& other)
{
  if (other.isEmpty() == false)
  {
    for (size_t i = 1; i <= other.top_; ++i)
    {
      out << other.array_[i] << " ";
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
  if (isEmpty() == true)
  {
    throw StackUnderflow< T >();
  }
  return array_[top_--];
}

template < class T >
bool StackArray< T >::isEmpty() const
{
  return top_ == 0;
}

template < class T >
void StackArray< T >::swap(StackArray< T >& other)
{
  std::swap(array_, other.array_);
  std::swap(top_, other.top_);
  std::swap(size_, other.size_);
}

#endif
