#ifndef __VALUE_HPP
#define __VALUE_HPP

template<char c>
struct C
{
  typedef char Type;
  static const char Value = c;
};

template<int i>
struct I
{
  typedef int Type;
  static const int Value = i;
};

template<typename V>
struct INC;

template<int i>
struct INC<I<i>> {
  static const int ResultValue = i + 1;
  typedef I<ResultValue> Result;
};

template<char a, char b>
struct C_TUPLE
{
  typedef char Type;

  static const char A = a;
  static const char B = b;
};

template<typename _A, typename _B>
struct TUPLE
{
  typedef _A A;
  typedef _B B;
};

#endif
