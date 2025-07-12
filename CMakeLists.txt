cmake_minimum_required(VERSION 3.10)
project(DiskSchedulingAlgorithms)

set(CMAKE_CXX_STANDARD 11)

add_executable(DiskSchedulingAlgorithms
    src/main.cpp
    src/DiskScheduler.cpp
)