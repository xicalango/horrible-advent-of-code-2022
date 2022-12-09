#ifndef __DAY1_EXAMPLE_INPUT_HPP
#define __DAY1_EXAMPLE_INPUT_HPP

#include "../list.hpp"
#include "../value.hpp"

namespace Day1Example
{

    typedef L<I<1000>,
              L<I<2000>,
                L<I<3000>,
                  LE>>>
        BUCKET_1;

    typedef L<I<4000>, LE> BUCKET_2;

    typedef L<I<5000>,
              L<I<6000>,
                LE>>
        BUCKET_3;

    typedef L<I<7000>,
              L<I<8000>,
                L<I<9000>,
                  LE>>>
        BUCKET_4;

    typedef L<I<10000>, LE> BUCKET_5;

    typedef L<BUCKET_1,
              L<BUCKET_2,
                L<BUCKET_3,
                  L<BUCKET_4,
                    LE>>>>
        BUCKETS;
};

#endif
