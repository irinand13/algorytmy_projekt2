//
// Created by iraan on 02.05.2026.
//

#ifndef GRAPH_H
#define GRAPH_H

#include "Array.h"
#include "Edge.h"
#include "SinglyLinkedList.h"

class Graph {
    int vertexCount = 0;
    SinglyLinkedList<Edge> adjacencyList;
    Array<Array<int>> adjacencyMatrix;
    public:

    //inicjalizacja grafy
    Graph(int n) {
        this->vertexCount = n;

        //reprezentacja listowa
        adjacencyList = SinglyLinkedList<Edge>();

        // reprezentacja macierzowa
        adjacencyMatrix = Array<Array<int>>(vertexCount);

        for (int i = 0; i < vertexCount; i++) {
            adjacencyMatrix[i] = Array<int>(vertexCount);

            for (int j = 0; j < vertexCount; j++) {
                adjacencyMatrix[i][j] = 0;
            }
        }
    }

    void addEdge(int dir, int wieght) {

    }

};
#endif //GRAPH_H
