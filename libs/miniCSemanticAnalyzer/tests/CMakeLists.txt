cmake_minimum_required(VERSION 3.27)
project(miniCSemanticAnalyzer-unit-tests)

if(${PROJECT_IS_TOP_LEVEL})
    enable_testing()
    find_package(miniCSemanticAnalyzer REQUIRED)
endif()

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(
    GLOB sources "*.cpp"
)

enable_testing()

add_executable(miniCSemanticAnalyzer-unit-tests ${sources} ${headers})

target_link_libraries(miniCSemanticAnalyzer-unit-tests
    miniCSemanticAnalyzer::miniCSemanticAnalyzer
    GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(miniCSemanticAnalyzer-unit-tests)