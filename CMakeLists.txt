# cmake_minimum_required(VERSION <specify CMake version here>)
project(inf_calc C)

set(CMAKE_C_STANDARD 99)

add_executable(inf_calc input.txt InfinityCalculator.c InfixToPostfix.c Input.c PostCalculator.c main.c)