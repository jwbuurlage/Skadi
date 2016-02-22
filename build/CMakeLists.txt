cmake_minimum_required(VERSION 3.0.0)

project(skadi)

include_directories(
    "../include"
    "../ext/jwutil/include"
    "../ext/catch/include"
)
link_directories(${CMAKE_BINARY_DIR}/../bin/)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wfatal-errors -Wextra -g -O3")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

set(LIB_NAME "skadi")
set(APP_NAME "simple_interface")
set(APP_SOURCE "../interface/simple.cpp")

set(
    LIB_SOURCES
    "../src/engine.cpp"
    "../src/evaluator.cpp"
    "../src/game/board.cpp"
    "../src/game/game.cpp"
    "../src/game/moves.cpp"
    "../src/game/pieces.cpp"
    "../src/searcher.cpp"
    "../src/util/logging.cpp"
    "../src/util/notation.cpp"
)

add_library( ${LIB_NAME} STATIC ${LIB_SOURCES} )

add_executable(${APP_NAME} ${APP_SOURCE})
target_link_libraries( ${APP_NAME} ${LIB_NAME} )
