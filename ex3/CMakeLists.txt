cmake_minimum_required(VERSION 3.12)
project(Ex3)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS} -std=c++11 -pthread -Wall -Wextra -Wvla")
add_executable(Ex3 MapReduceClient.cpp MapReduceClient.h MapReduceFramework.cpp MapReduceFramework.h Barrier.cpp Barrier.h joinTest.cpp)