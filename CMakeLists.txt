cmake_minimum_required(VERSION 2.8)
project(Akiama)

set(Akiama_VERSION_MAJOR 0)
set(Akiama_VERSION_MINOR 1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

option(WITH_TESTS "enable the build of test" ON)

add_subdirectory(src)
