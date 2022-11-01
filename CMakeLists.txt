cmake_minimum_required(VERSION 3.23)
project(process_party)

set(CMAKE_CXX_STANDARD 23)

# Add dynamic library
include_directories(lib/include)
file(GLOB_RECURSE validator_LIBRARY_SOURCES lib/src/*)
file(GLOB_RECURSE validator_LIBRARY_HEADERS lib/headers/*)

if (MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
endif()

add_library(validator_lib SHARED ${validator_LIBRARY_SOURCES}
                                 ${validator_LIBRARY_HEADERS})

# Add GoogleTest
include(FetchContent)
FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest
        GIT_TAG release-1.11.0)
FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BUILD_DIR})
endif()

# Compile examples
add_executable(validator_example examples/launch_validator.cpp)
target_link_libraries(validator_example validator_lib)

# Compile tests
add_executable(validator_test tests/test_validator.cpp)
target_link_libraries(validator_test validator_lib gtest_main)
