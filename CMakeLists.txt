cmake_minimum_required(VERSION 3.27)
project(miniCTranslator 
        VERSION 0.1.0 
        LANGUAGES C CXX)
set (CMAKE_CXX_STANDARD 20)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

option(MINICTRANSLATOR_TESTING "Enable unit-tests" ON)

add_subdirectory(libs/miniCLexer)
add_subdirectory(libs/miniCBuilderAST)
add_subdirectory(libs/miniCSemanticAnalyzer)
include_directories(libs/)

file(
    GLOB SOURCES "sources/*.cpp"
    GLOB HEADERS "include/*.h"
)

add_executable(miniCTranslator main.cpp ${SOURCES} ${HEADERS})

target_link_libraries(miniCTranslator miniCLexer)
target_link_libraries(miniCTranslator miniCBuilderAST)
target_link_libraries(miniCTranslator miniCSemanticAnalyzer)


if(MINICTRANSLATOR_TESTING)
    enable_testing()
endif()