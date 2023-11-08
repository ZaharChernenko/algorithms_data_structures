cmake_minimum_required(VERSION 3.26)
project(linear_search)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(linear_search
        "A(isAscending).h"
        "B(seqType).h"
        "C(nearestNum).h"
        "D(localMax).h"
        "E(cowChamp).h"
        "F(symmetrical).h"
        "G(mul2).h"
        "H(mul3).h"
        inputs.h
        main.cpp
        "I (sapper).h")
