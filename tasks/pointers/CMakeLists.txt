cmake_minimum_required(VERSION 3.26)
project(pointers C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(C++)

add_executable(pointers
        C++/3Sum.h
        C++/longestPalindrome.h)
