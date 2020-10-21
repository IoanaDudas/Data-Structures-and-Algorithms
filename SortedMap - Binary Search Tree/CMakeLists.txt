cmake_minimum_required(VERSION 3.16)
project(Assignment_6___SortedMap)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Assignment_6___SortedMap
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        ShortTest.cpp
        ShortTest.h
        SMIterator.cpp
        SMIterator.h
        SortedMap.cpp
        SortedMap.h)
