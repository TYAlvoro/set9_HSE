cmake_minimum_required(VERSION 3.31)
project(set9)

set(CMAKE_CXX_STANDARD 20)

add_executable(set9 StringGenerator.h
        main.cpp
        StringSortTester.h
        main_baseline.cpp
        StringAlgos.h
)
