#!/usr/bin/env python3

buckets = []

with open("day1-calories.txt") as f:
    current_bucket = []

    for line in f:
        line = line.strip()
        if len(line) == 0:
            buckets.append(current_bucket)
            current_bucket = []
        else:
            current_bucket.append(int(line))
    
    if len(current_bucket) > 0:
        buckets.append(current_bucket)


with open("day1-calories.hpp", 'w') as f:
    print("""#ifndef __DAY1_CALORIES_HPP
#define __DAY1_CALORIES_HPP

#include "../list.hpp"
#include "../value.hpp"

namespace Day1Input {""", file = f)

    for i, bucket in enumerate(buckets):
        print("typedef ", file = f)
        for value in bucket:
            print(f"L<I<{value}>,", file = f)
        
        print("LE", file = f)
        for _ in range(len(bucket)):
            print(">", end="", file = f)
        
        print(file = f)
        print(f"BUCKET_{i};", file = f)
        print(file = f)

    print("typedef ", file = f)
    for i in range(len(buckets)):
        print(f"L<BUCKET_{i},", file = f)
    print("LE", file=f)
    for _ in range(len(buckets)):
        print(">", end="", file = f)
    print(file=f)    
    print("BUCKETS;", file = f)
    print(file=f)    

    print("""
}
#endif""", file=f)
