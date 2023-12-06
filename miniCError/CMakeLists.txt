cmake_minimum_required(VERSION 3.27)
project(miniCError VERSION 0.1.0 LANGUAGES C CXX)
set (CMAKE_CXX_STANDARD 20)

include(CTest)
enable_testing()

add_library(miniCError miniCError.cpp miniCError.h)
target_include_directories(miniCError PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})