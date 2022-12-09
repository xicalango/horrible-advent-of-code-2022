
#include <iostream>
#include <limits>

#include "list.hpp"
#include "value.hpp"
#include "print.hpp"
#include "control.hpp"

#include "input/day1_example_input.hpp"
#include "input/day1-calories.hpp"

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

template<typename List, typename CurrentMax>
struct _MAX {
    typedef typename IF<
       (List::Head::Value > CurrentMax::Value),
       typename _MAX<typename List::Tail, typename List::Head>::Result,
       typename _MAX<typename List::Tail, CurrentMax>::Result
       >::Result Result;
};

template<typename CurrentMax>
struct _MAX<LE, CurrentMax> {
    typedef CurrentMax Result;
};

template<typename List>
struct MAX {
    typedef typename _MAX<List, I<std::numeric_limits<int>::lowest()>>::Result Result;
};

int main(void) {

    typedef MAP<Day1Example::BUCKETS, SUM_INT>::Result MAPPED;
    typedef MAX<MAPPED>::Result RESULT;

    PRINT_LIST<MAPPED>::print();

    std::cout << "max: ";
    PRINT<RESULT>::print();

    typedef MAP<Day1Input::BUCKETS, SUM_INT>::Result D1_MAPPED;
    typedef MAX<D1_MAPPED>::Result D1_RESULT;

    std::cout << "max day1: ";
    PRINT<D1_RESULT>::print();
}
