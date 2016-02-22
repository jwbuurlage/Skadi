cmake_minimum_required(VERSION 3.0.0)

project(skadi_tests)

include_directories(
    "../../include"
    "../../ext/jwutil/include"
    "../../ext/catch/include"
)
link_directories(${CMAKE_BINARY_DIR}/../../bin/)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wfatal-errors -Wextra -g -O3")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../bin)

set(LIB_NAME "skadi")
set(TEST_NAME "skadi_tests")

set(
    TEST_SOURCES
    "../catch.cpp"
    "../game_rules.cpp"
    "../notation.cpp"
)

add_executable(${TEST_NAME} ${TEST_SOURCES})
target_link_libraries( ${TEST_NAME} ${LIB_NAME} )
