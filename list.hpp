#ifndef __LIST_HPP
#define __LIST_HPP

#include <iostream>

#include "value.hpp"
#include "control.hpp"

template<typename H, typename T>
struct L
{
  typedef H Head;
  typedef T Tail;
};

struct LE {};

template<typename List>
void print() {
  std::cout << List::Head::Value;
  print<typename List::Tail>();
}

template<>
void print<LE>() {}
  
template<typename List, typename Value>
struct STACK_PUSH
{
  typedef L<Value, List> Result;
};

template<typename List>
struct STACK_POP
{
  typedef typename List::Head Value;
  typedef typename List::Tail Result;
};

template<typename List, int start>
struct SLICE
{
  typedef typename SLICE<typename List::Tail, start-1>::Result Result;
};

template<typename List>
struct SLICE<List, 0>
{
  typedef List Result;
};

template<typename List>
struct LEN {
  static const int ResultValue = 1 + LEN<typename List::Tail>::ResultValue;
};

template<>
struct LEN<LE> {
  static const int ResultValue = 0;
};


template<typename List>
struct SUM_INT {

    static const int ResultValue = List::Head::Value + SUM_INT<typename List::Tail>::ResultValue;

    typedef I<ResultValue> Result;
};

template<>
struct SUM_INT<LE> {
    static const int ResultValue = 0;
    typedef I<ResultValue> Result;
};

template<typename List, template<typename A> typename F>
struct MAP {
    typedef L < 
            typename F<typename List::Head>::Result, 
            typename MAP<typename List::Tail, F>::Result 
        > Result;
};

template<template<typename A> typename F>
struct MAP<LE, F> {
    typedef LE Result;
};

template<typename List, template<typename A> typename Filter>
struct FILTER {

  typedef FILTER<typename List::Tail, Filter> TailFilter;

  typedef typename IF<
    Filter<typename List::Head>::ResultValue,
    L<typename List::Head, typename TailFilter::Result>,
    typename TailFilter::Result
  >::Result Result;

};

template<template<typename A> typename Filter>
struct FILTER<LE, Filter> {
  typedef LE Result;
};

template<typename List1, typename List2>
struct CONCAT {
  typedef L<typename List1::Head, typename CONCAT<typename List1::Tail, List2>::Result> Result;
};

template<typename List2>
struct CONCAT<LE, List2> {
  typedef List2 Result;
};

template<typename List, typename V>
struct ZIP_WITH_INDEX {

  typedef L<
    TUPLE<V, typename List::Head>, 
    typename ZIP_WITH_INDEX<typename List::Tail, typename INC<V>::Result>::Result
  > Result;

};

template<typename V>
struct ZIP_WITH_INDEX<LE, V> {
  typedef LE Result;
};

#endif
