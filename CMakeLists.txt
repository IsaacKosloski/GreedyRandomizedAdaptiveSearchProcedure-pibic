cmake_minimum_required(VERSION 3.27)
project(GreedyRandomizedAdaptiveSearchProcedure_pibic)

set(CMAKE_CXX_STANDARD 14)

include_directories(TSP/Sequential/src)

add_executable(GreedyRandomizedAdaptiveSearchProcedure_pibic
        TSP/runHelper/src/main.cpp
        TSP/Sequential/src/component.cpp
        TSP/Sequential/src/component.h
        TSP/Sequential/src/functions.cpp
        TSP/Sequential/src/functions.h
        TSP/Sequential/src/main.cpp
        TSP/Sequential/src/node.cpp
        TSP/Sequential/src/node.h
        TSP/Sequential/src/scanner.cpp
        TSP/Sequential/src/scanner.h
        TSP/Sequential/src/mainExec.cpp)
