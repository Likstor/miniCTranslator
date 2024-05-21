cmake_minimum_required(VERSION 3.27)

project(miniCAtomsToIntel8080 VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)

# option(MINICATOMSTOINTEL8080_TESTING "Enable unit-testing" ON)

if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

add_library(miniCAtomsToIntel8080 STATIC)

target_sources(${PROJECT_NAME}
    PRIVATE
        source/translator.cpp
)

target_include_directories(miniCAtomsToIntel8080
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/source
        ${CMAKE_CURRENT_SOURCE_DIR}/libs
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(miniCAtomsToIntel8080 INTERFACE cxx_std_20)

add_library(miniCAtomsToIntel8080::miniCAtomsToIntel8080 ALIAS miniCAtomsToIntel8080)

target_link_libraries(miniCAtomsToIntel8080 miniCSemanticAnalyzer)

install(DIRECTORY include/miniCAtomsToIntel8080 DESTINATION include)

install(TARGETS miniCAtomsToIntel8080 EXPORT miniCAtomsToIntel8080Config)
install(EXPORT miniCAtomsToIntel8080Config NAMESPACE miniCAtomsToIntel8080:: DESTINATION share/miniCAtomsToIntel8080/cmake)

include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_BINARY_DIR}/miniCAtomsToIntel8080ConfigVersion.cmake"
    VERSION
        ${PROJECT_VERSION}
    COMPATIBILITY
        AnyNewerVersion
)
install(FILES "${PROJECT_BINARY_DIR}/miniCAtomsToIntel8080ConfigVersion.cmake" DESTINATION share/miniCAtomsToIntel8080/cmake)

# if(MINICATOMSTOINTEL8080_TESTING)
#     enable_testing()
#     # add_subdirectory(tests)
# endif()