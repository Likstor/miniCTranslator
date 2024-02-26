cmake_minimum_required(VERSION 3.28)
project(miniCTranslator 
        VERSION 0.1.0 
        LANGUAGES C CXX)
set (CMAKE_CXX_STANDARD 20)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

option(MINICTRANSLATOR_TESTING "Enable unit-tests" OFF)

add_subdirectory(libs/miniCLexer)

add_executable(miniCTranslator main.cpp ${SOURCES})

target_link_libraries(miniCTranslator miniCLexer)

if(MINICTRANSLATOR_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()