cmake_minimum_required(VERSION 3.27)
project(miniCLexicalAnalyzer VERSION 0.1.0 LANGUAGES C CXX)
set (CMAKE_CXX_STANDARD 20)

include(CTest)
enable_testing()

add_library(miniCLexicalAnalyzer miniCLexicalAnalyzer.cpp miniCLexicalAnalyzer.h)
target_include_directories(miniCLexicalAnalyzer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})