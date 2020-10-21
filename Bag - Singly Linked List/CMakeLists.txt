cmake_minimum_required(VERSION 3.15)
project(Assignment_2___Bag)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Assignment_2___Bag
        App.cpp
        Bag.cpp
        Bag.h
        BagIterator.cpp
        BagIterator.h
        ExtendedTest.cpp
        ExtendedTest.h
        ShortTest.cpp
        ShortTest.h)
