cmake_minimum_required(VERSION 3.28)
project(algorytmy_projekt2)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED)

add_executable(algorytmy_projekt2 main.cpp
        include/Graph.h
        include/Array.h
        include/SinglyLinkedList.h
        include/KruskalAlgorithm.h
        include/DijkstraAlgorithm.h
        include/BellmanFordAlgorithm.h
        include/FordFulkersonAlgorithm.h
        include/PrimAlgorithm.h
        lib/Parameters.h
        include/GenerateGraph.h
        include/quickSort.h
        include/FileReader.h
        include/FileWriter.h
        include/Runner.h)

target_include_directories(algorytmy_projekt2 PRIVATE
        include
        lib
        ${Boost_INCLUDE_DIRS}
)

target_link_libraries(algorytmy_projekt2 PRIVATE
        ${CMAKE_SOURCE_DIR}/lib/libparameters.so
        parameters
        ${Boost_LIBRARIES}
)

target_compile_options(algorytmy_projekt2 PRIVATE
        -Wall -Wextra -Werror
)

add_executable(algorytmy_dataset main_dataset.cpp)

target_include_directories(algorytmy_dataset PRIVATE
        include
        lib
        ${Boost_INCLUDE_DIRS}
)

target_link_libraries(algorytmy_dataset PRIVATE
        ${CMAKE_SOURCE_DIR}/lib/libparameters.so
        parameters
        ${Boost_LIBRARIES}
)