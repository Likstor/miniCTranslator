cmake_minimum_required(VERSION 3.27)

project(miniCLexer VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)

option(MINICLEXER_TESTING "Enable unit-testing" ON)

if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

add_library(miniCLexer STATIC)

target_sources(${PROJECT_NAME}
    PRIVATE
        source/lexer.cpp
)

target_include_directories(miniCLexer
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/source
        ${CMAKE_CURRENT_SOURCE_DIR}/libs
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(miniCLexer INTERFACE cxx_std_20)

add_library(miniCLexer::miniCLexer ALIAS miniCLexer)

install(DIRECTORY include/miniCLexer DESTINATION include)

install(TARGETS miniCLexer EXPORT miniCLexerConfig)
install(EXPORT miniCLexerConfig NAMESPACE miniCLexer:: DESTINATION share/miniCLexer/cmake)

include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_BINARY_DIR}/miniCLexerConfigVersion.cmake"
    VERSION
        ${PROJECT_VERSION}
    COMPATIBILITY
        AnyNewerVersion
)
install(FILES "${PROJECT_BINARY_DIR}/miniCLexerConfigVersion.cmake" DESTINATION share/miniCLexer/cmake)

if(MINICLEXER_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()