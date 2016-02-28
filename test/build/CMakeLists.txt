cmake_minimum_required(VERSION 3.0.0)

project(skadi_tests)

include_directories(
    "../../include"
    "../../ext/jwutil/include"
    "../../ext/catch/include"
)
link_directories(${CMAKE_BINARY_DIR}/../../bin/)

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
