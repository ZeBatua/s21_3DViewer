#!/bin/bash

cp ../materials/linters/.clang-format .


clang-format -i Widget/c_part/*.c
clang-format -i Widget/c_part/*.h
clang-format -i tests/test.c
clang-format -i Widget/*.cpp
clang-format -i Widget/*.h


rm .clang-format 


