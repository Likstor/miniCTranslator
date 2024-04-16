cmake_minimum_required(VERSION 3.27)

project(miniCSemanticAnalyzer VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)

option(MINICSEMANTIC_TESTING "Enable unit-testing" ON)

if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

add_library(miniCSemanticAnalyzer STATIC)

target_sources(${PROJECT_NAME}
    PRIVATE
        source/analyzer.cpp
)

target_include_directories(miniCSemanticAnalyzer
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/source
        ${CMAKE_CURRENT_SOURCE_DIR}/libs
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(miniCSemanticAnalyzer INTERFACE cxx_std_20)

target_link_libraries(miniCSemanticAnalyzer miniCBuilderAST)


add_library(miniCSemanticAnalyzer::miniCSemanticAnalyzer ALIAS miniCSemanticAnalyzer)

install(DIRECTORY include/miniCSemanticAnalyzer DESTINATION include)

install(TARGETS miniCSemanticAnalyzer EXPORT miniCSemanticAnalyzerConfig)
install(EXPORT miniCSemanticAnalyzerConfig NAMESPACE miniCSemanticAnalyzer:: DESTINATION share/miniCSemanticAnalyzer/cmake)

include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_BINARY_DIR}/miniCSemanticAnalyzerConfigVersion.cmake"
    VERSION
        ${PROJECT_VERSION}
    COMPATIBILITY
        AnyNewerVersion
)
install(FILES "${PROJECT_BINARY_DIR}/miniCSemanticAnalyzerConfigVersion.cmake" DESTINATION share/miniCSemanticAnalyzer/cmake)

if(MINICSEMANTIC_TESTING)
    enable_testing()
    # add_subdirectory(tests)
endif()