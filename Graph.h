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
    Array<Array<int>> incidencyMatrix;
    int edgeCount = 0;
    public:

    // inicjalizacja grafu
    // tworzy listę ora
    explicit Graph(int n) {
        this->vertexCount = n;

        //reprezentacja listowa
        adjacencyList = new SinglyLinkedList<Edge>[vertexCount];

        // reprezentacja macierzowa
        incidencyMatrix = Array<Array<int>>(vertexCount);

        for (int i = 0; i < vertexCount; i++) {
            incidencyMatrix[i] = Array<int>(edgeCount);

            for (int j = 0; j < edgeCount; j++) {
                incidencyMatrix[i][j] = 0;
            }
        }
    }

    //Metoda dodawania nowej krawędzi
    // Dodaje krawiędź do listy oraz do macierzy incydencji
    void addEdgeToList(int u, int v, int weight) {

        if (weight < 0) {
            throw std::invalid_argument("weight cannot be negative");
        }

        Edge newEdge(v, weight);

        adjacencyList[u].push(newEdge);
    }

    void addToMatrixDirected(int u, int v, int weight) {
        if (weight < 0) {
            throw std::invalid_argument("weight cannot be negative");
        }
        incidencyMatrix[u][edgeCount] = -1;
        incidencyMatrix[v][edgeCount] = 1;
    }

    void addToMatrix(int u, int v, int weight) {
        if (weight < 0) {
            throw std::invalid_argument("weight cannot be negative");
        }
        incidencyMatrix[u][edgeCount] = 1;
        incidencyMatrix[v][edgeCount] = 1;
    }


};
#endif //GRAPH_H
