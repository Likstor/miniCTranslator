cmake_minimum_required(VERSION 3.28)
project(miniCLexer-unit-tests)

if(${PROJECT_IS_TOP_LEVEL})
    enable_testing()
    find_package(miniCLexer REQUIRED)
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

add_executable(miniCLexer-unit-tests ${sources} ${headers})

target_link_libraries(miniCLexer-unit-tests
    miniCLexer::miniCLexer
    GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(miniCLexer-unit-tests)