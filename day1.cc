
#include <iostream>
#include <limits>

#include "list.hpp"
#include "value.hpp"
#include "print.hpp"
#include "control.hpp"

#include "input/day1_example_input.hpp"
#include "input/day1-calories.hpp"




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


template<typename List, typename CM1, typename CM2, typename CM3>
struct _MAX3 {
    typedef typename IF<
        (List::Head::Value > CM3::Value),
        /*then*/ typename IF<
            (List::Head::Value > CM2::Value),
            /*then*/ typename IF<
                (List::Head::Value > CM1::Value),
                /*then*/ typename _MAX3<typename List::Tail, typename List::Head, CM1, CM2>::Result,
                /*else*/ typename _MAX3<typename List::Tail, CM1, typename List::Head, CM2>::Result
                >::Result,
            /*else*/ typename _MAX3<typename List::Tail, CM1, CM2, typename List::Head>::Result
            >::Result,
        /*else*/ typename _MAX3<typename List::Tail, CM1, CM2, CM3>::Result
    >::Result Result;
};

template<typename CM1, typename CM2, typename CM3>
struct _MAX3<LE, CM1, CM2, CM3> {
    typedef L<CM1, L<CM2, L<CM3, LE>>> Result;
};

template<typename List>
struct MAX3 {
    typedef typename _MAX3<List, I<std::numeric_limits<int>::lowest()>, I<std::numeric_limits<int>::lowest()>, I<std::numeric_limits<int>::lowest()>>::Result Result;
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

    typedef MAX3<MAPPED>::Result TOP3_E_RESULT;

    std::cout << "top3 ex:" << std::endl;
    PRINT_LIST<TOP3_E_RESULT>::print();

    typedef SLICE<D1_MAPPED, 190>::Result SLICED;

    std::cout << "len e10: " << LEN<SLICED>::ResultValue << std::endl;

    //typedef MAX3<SLICED>::Result TOP3_E10_RESULT;
    //std::cout << "top3 e10:" << std::endl;
    //PRINT_LIST<TOP3_E10_RESULT>::print();
}
