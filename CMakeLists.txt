cmake_minimum_required(VERSION 3.15)
project(process_party)

set(CMAKE_CXX_STANDARD 23)

if (MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
endif()

include_directories(${CMAKE_SOURCE_DIR})

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

# Compilation of validator (test project)

file(GLOB_RECURSE validator_LIBRARY validator/validator.cpp
                                    validator/validator.h)
add_library(validator_lib SHARED ${validator_LIBRARY})

add_executable(example_validator validator/launch_validator.cpp)
target_link_libraries(example_validator validator_lib)

add_executable(test_validator validator/test_validator.cpp)
target_link_libraries(test_validator validator_lib gtest_main)

# Compilation of process party

# Process party dynamic library
file(GLOB_RECURSE process_party_LIBRARY process_party/*)
add_library(process_party SHARED ${process_party_LIBRARY})

# Compile examples
file(GLOB_RECURSE examples_list examples/*)
foreach(example ${examples_list})
    get_filename_component(example_base ${example} NAME_WLE)
    add_executable(${example_base} ${example})
    target_link_libraries(${example_base} process_party)
endforeach()

# Compile tests
file(GLOB_RECURSE tests_list tests/*)
foreach(test ${tests_list})
    get_filename_component(test_base ${test} NAME_WLE)
    message(STATUS ${test_base})
    add_executable(${test_base} ${test})
    target_link_libraries(${test_base} process_party gtest_main)
endforeach()
