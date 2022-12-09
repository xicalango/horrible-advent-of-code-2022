#!/usr/bin/env python3

with open("day2-guide.txt") as f, open("day2-guide.hpp", 'w') as of:

    print("""#ifndef __DAY2_GUIDE_HPP
#define __DAY2_GUIDE_HPP

#include "../list.hpp"
#include "../value.hpp"

namespace Day2 {
typedef
""", file=of)

    c = 0
    for line in f:
        moves = line.strip().split(" ")

        print(f"L<C_TUPLE<'{moves[0]}', '{moves[1]}'>,", file=of)
    
        c += 1
    print("LE", file=of)
    print("".join([">"] * c), file=of)
    print("MOVES;", file=of)

    print("""}
#endif
""", file=of)


