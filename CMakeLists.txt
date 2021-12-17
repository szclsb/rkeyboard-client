cmake_minimum_required(VERSION 3.20)
project(rkb)

set(CMAKE_CXX_STANDARD 20)

# dependencies first
add_subdirectory(vendors)
# main project
add_subdirectory(src)

# test module second
#add_subdirectory(Google_tests)