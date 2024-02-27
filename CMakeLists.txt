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

file(
    GLOB SOURCES "sources/*.cpp"
    GLOB HEADERS "include/*.h"
)

target_include_directories(miniCLexer
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/source
        ${CMAKE_CURRENT_SOURCE_DIR}/libs
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

add_executable(miniCTranslator main.cpp ${SOURCES} ${HEADERS})

target_link_libraries(miniCTranslator miniCLexer)


if(MINICTRANSLATOR_TESTING)
    add_compile_options("-DMINICLEXERE_TESTING=ON")
    enable_testing()
    add_subdirectory(tests)
endif()