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
    SinglyLinkedList<Edge>* adjacencyList;
    Array<Array<int>> adjacencyMatrix;
    public:

    //inicjalizacja grafy
    explicit Graph(int n) {
        this->vertexCount = n;

        //reprezentacja listowa
        adjacencyList = new SinglyLinkedList<Edge>[vertexCount];

        // reprezentacja macierzowa
        adjacencyMatrix = Array<Array<int>>(vertexCount);

        for (int i = 0; i < vertexCount; i++) {
            adjacencyMatrix[i] = Array<int>(vertexCount);

            for (int j = 0; j < vertexCount; j++) {
                adjacencyMatrix[i][j] = 0;
            }
        }
    }

    void addEdge(int u, int v, int weight) {

        if (weight < 0) {
            throw std::invalid_argument("weight cannot be negative");
        }

        auto newEdge = new Edge(v, weight);

        adjacencyList[u].push(*newEdge);

        adjacencyMatrix[u][v] = weight;
    }


};
#endif //GRAPH_H
