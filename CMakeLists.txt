cmake_minimum_required(VERSION 3.17)
project(bioinformatics_fall2020_hw2__copy_)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(hw1)
include_directories(hw1/rank_support)
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

add_definitions("-lsdsl -ldivsufsort -ldivsufsort64")

add_executable(bioinformatics_fall2020_hw2__copy_
        run_bbhash.cpp
        xxhash.c)

target_link_libraries(bioinformatics_fall2020_hw2__copy_ sdsl)