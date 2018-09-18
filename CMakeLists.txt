cmake_minimum_required(VERSION 2.8)

project(fastxml)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O3 -pthread -g")

add_executable(fastxml test.cpp)
