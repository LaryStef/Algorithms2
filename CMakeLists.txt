cmake_minimum_required(VERSION 3.15)

project(ADT_Graph VERSION 1.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
add_executable(
    graph_test
    src/main.cpp
    src/directed_graph.cpp
    src/find_paths.cpp
)
