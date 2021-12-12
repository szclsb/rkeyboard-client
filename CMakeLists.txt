cmake_minimum_required(VERSION 3.20)
project(rkeyboard_client)

set(CMAKE_CXX_STANDARD 20)

# main module first
add_subdirectory(src)

# test module second
#add_subdirectory(Google_tests)