cmake_minimum_required(VERSION 3.8)
project(lab4_B)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Barrier.cpp
        Barrier.h
        reusableBarrier.cpp
        Semaphore.cpp
        Semaphore.h)

add_executable(lab4_B ${SOURCE_FILES})