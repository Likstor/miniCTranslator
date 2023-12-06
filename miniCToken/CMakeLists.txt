cmake_minimum_required(VERSION 3.27)
project(miniCToken VERSION 0.1.0 LANGUAGES C CXX)
set (CMAKE_CXX_STANDARD 20)

include(CTest)
enable_testing()

add_library(miniCToken miniCToken.cpp miniCToken.h)
target_include_directories(miniCToken PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})