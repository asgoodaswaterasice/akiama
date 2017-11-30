cmake_minimum_required(VERSION 2.8)
project(Akiama)

set(Akiama_VERSION_MAJOR 0)
set(Akiama_VERSION_MINOR 1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")

option(WITH_TESTS "enable the build of test" ON)
if(WITH_TESTS)
	find_package(gtest REQUIRED)
endif()

add_subdirectory(src)
