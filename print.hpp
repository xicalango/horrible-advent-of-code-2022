#ifndef __PRINT_HPP
#define __PRINT_HPP

#include <iostream>

#include "list.hpp"
#include "value.hpp"

template<typename V>
struct PRINT { };

template<typename H, typename T>
struct PRINT<L<H, T>> {
    static void print() {
        PRINT<H>::print();
        PRINT<T>::print();
    }
};

template<>
struct PRINT<LE> {
    static void print() {
    }
};

template<typename List, char sep = '\n'>
struct PRINT_LIST {

    static void print() {
        std::cout << List::Head::Value << sep;
        PRINT_LIST<typename List::Tail, sep>::print();
    }

};

template<char sep>
struct PRINT_LIST<LE, sep> {
    static void print() {
    }
};

template<int i>
struct PRINT<I<i>> {
    static void print() {
        std::cout << i << std::endl;
    }
};

template<char c>
struct PRINT<C<c>> {
    static void print() {
        std::cout << c << std::endl;
    }
};

template<char a, char b>
struct PRINT<C_TUPLE<a, b>> {
    static void print() {
        std::cout << '(' << a << ',' << b << ')' << std::endl;
    }
};

template<typename A, typename B>
struct PRINT<TUPLE<A, B>> {
    static void print() {
        std::cout << "T(" << std::endl;
        PRINT<A>::print();
        PRINT<B>::print();
        std::cout << ")T" << std::endl;
    }
};

#endif
