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
        PRINT_LIST<L<H, T>>::print();
    }
};

template<>
struct PRINT<LE> {
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

#endif
