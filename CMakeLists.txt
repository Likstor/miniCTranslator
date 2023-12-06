cmake_minimum_required(VERSION 3.27)
project(miniCTranslator VERSION 0.1.0 LANGUAGES C CXX)
set (CMAKE_CXX_STANDARD 20)

include(CTest)
enable_testing()

add_executable(main main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_subdirectory(miniCLexicalAnalyzer)
target_link_libraries(main miniCLexicalAnalyzer)
add_subdirectory(miniCToken)
target_link_libraries(main miniCToken)
add_subdirectory(miniCError)
target_link_libraries(main miniCError)