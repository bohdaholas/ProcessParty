cmake_minimum_required(VERSION 3.23)
project(process_party)

set(CMAKE_CXX_STANDARD 23)

include_directories(lib/include)
include(FetchContent)
FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest
        GIT_TAG release-1.11.0)
FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BUILD_DIR})
endif()

add_executable(validator_example
        examples/launch_validator.cpp
        lib/src/validator.cpp)

add_executable(validator_test
        tests/test_validator.cpp
        lib/src/validator.cpp)
target_link_libraries(validator_test gtest_main)
