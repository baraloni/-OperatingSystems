cmake_minimum_required(VERSION 3.12)
project(Ex4)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS} -std=c++11 -pthread -Wall -Wextra -Wvla")
add_executable(Ex4 VirtualMemory.cpp VirtualMemory.h PhysicalMemory.cpp PhysicalMemory.h MemoryConstants.h SimpleTest.cpp)