cmake_minimum_required(VERSION 2.8)
project(Akiama)

set(Akiama_VERSION_MAJOR 0)
set(Akiama_VERSION_MINOR 1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

add_subdirectory(src)
