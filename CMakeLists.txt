cmake_minimum_required(VERSION 3.29)
project(algorytmy_projekt2)

set(CMAKE_CXX_STANDARD 17)

add_executable(algorytmy_projekt2 main.cpp
        include/Graph.h
        include/Array.h
        include/SinglyLinkedList.h
        include/KruskalAlgorithm.h
        include/DijkstraAlgorithm.h
        "include/BellmanFordAlgorithm.h"
        "include/FordFulkersonAlgorithm .h"
        include/PrimAlgorithm.h
        "include/Parameters.h"
        include/GenerateGraph.h)


target_include_directories(algorytmy_projekt2 PRIVATE
        include
        lib
)

target_compile_options(algorytmy_projekt2 PRIVATE
        -Wall
        -Wextra
        -Werror
)
