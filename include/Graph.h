//
// Created by iraan on 02.05.2026.
//

#ifndef GRAPH_H
#define GRAPH_H
#include "Array.h"
#include "SinglyLinkedList.h"

struct Edge {
    int from;
    int to;
    int weight;

    Edge() = default;

    Edge(int u, int v, int weight) {
        this->from = u;
        this->to = v;
        this->weight = weight;
    }
};

class Graph {
    int vertexCount = 0;
    int edgeCount;
    bool directed;
    SinglyLinkedList<Edge>* adjacencyList;
    Array<Array<int>> incidencyMatrix;

    public:

    // inicjalizacja grafu
    // tworzy listę ora
    explicit Graph(int n, bool directed) {
        this->vertexCount = n;
        this->edgeCount = 0;
        this->directed = directed;

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
    void addEdge(int u, int v, int weight) {

        if (weight < 0) throw std::invalid_argument("weight cannot be negative");

        Edge newEdge(u, v, weight);

        adjacencyList[u].push(newEdge);
        if(!directed) {
            adjacencyList[v].push(newEdge);
        }

        if (directed) {
            incidencyMatrix[u][edgeCount] = -1;
            incidencyMatrix[v][edgeCount] = 1;
        } else {
            incidencyMatrix[u][edgeCount] = 1;
            incidencyMatrix[v][edgeCount] = 1;
        }

        edgeCount++;
    }



};
#endif //GRAPH_H
