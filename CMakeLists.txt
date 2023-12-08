cmake_minimum_required(VERSION 3.27)
project(miniCTranslator 
        VERSION 0.1.0 
        LANGUAGES C CXX)
set (CMAKE_CXX_STANDARD 20)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

include_directories(
    includes/
    libs/
)

file(
    GLOB SOURCES "source/*.cpp"
)

file(GLOB LIBS "libs/*.hpp")

add_executable(miniCTranslator main.cpp ${SOURCES})