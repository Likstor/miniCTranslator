cmake_minimum_required(VERSION 3.27)

project(miniCBuilderAST VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)

option(MINICBUILDERAST_TESTING "Enable unit-testing" ON)

if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

add_library(miniCBuilderAST STATIC)

target_sources(${PROJECT_NAME}
    PRIVATE
        source/builder.cpp
)

target_include_directories(miniCBuilderAST
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/source
        ${CMAKE_CURRENT_SOURCE_DIR}/libs
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(miniCBuilderAST INTERFACE cxx_std_20)

add_library(miniCBuilderAST::miniCBuilderAST ALIAS miniCBuilderAST)

target_link_libraries(miniCBuilderAST miniCLexer)

install(DIRECTORY include/miniCBuilderAST DESTINATION include)

install(TARGETS miniCBuilderAST EXPORT miniCBuilderASTConfig)
install(EXPORT miniCBuilderASTConfig NAMESPACE miniCBuilderAST:: DESTINATION share/miniCBuilderAST/cmake)

include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_BINARY_DIR}/miniCBuilderASTConfigVersion.cmake"
    VERSION
        ${PROJECT_VERSION}
    COMPATIBILITY
        AnyNewerVersion
)
install(FILES "${PROJECT_BINARY_DIR}/miniCBuilderASTConfigVersion.cmake" DESTINATION share/miniCBuilderAST/cmake)

if(MINICBUILDERAST_TESTING)
    enable_testing()
    # add_subdirectory(tests)
endif()