#!/usr/bin/env python3

def convert(input_file, output_file, name):
  with open(input_file) as f, open(output_file, 'w') as of:
    print(f"""#ifndef __DAY10_{name}_INPUT_HPP
#define __DAY10_{name}_INPUT_HPP

#include "../list.hpp"
#include "../value.hpp"

namespace Day10Input {{
typedef""", file = of)

    c = 0
    for line in f:
      line = line.strip()
      if line == "noop":
        print("L<C<'N'>,", file = of)
      else:
        addx = int(line.split(" ")[1])
        print(f"L<I<{addx}>,", file = of)
      c += 1
      
    print("LE", file = of)
    print("".join([">"] * c), file = of)
    print(f"{name};", file = of)
    print("""}
#endif""", file = of)

convert("day10_example.txt", "day10_example.hpp", "EXAMPLE1")
convert("day10.txt", "day10.hpp", "INPUT")
