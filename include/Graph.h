//
// Created by iraan on 02.05.2026.
//

#ifndef GRAPH_H
#define GRAPH_H
#include "Array.h"
#include "SinglyLinkedList.h"

//Reprezentacja krawędzi
struct Edge {
    int from;
    int to;
    unsigned int weight;

    Edge() = default;

    Edge(int u, int v, int weight) {
        this->from = u;
        this->to = v;
        this->weight = weight;
    }

    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }

    bool operator>(const Edge& other) const {
        return weight > other.weight;
    }
};


//Reprezentacja wierzchołka
struct Vertex {
    int id;
    bool colored;

    Vertex() = default;

    Vertex(int id, bool colored) {
        this->id = id;
        this->colored = colored;
    }

    void setColored() {
        this->colored = true;

    }
};

//Reprezentacja grafu
class Graph {
    int vertexCount = 0;
    int edgeCount;
    bool directed;
    Vertex* vertices;
    SinglyLinkedList<Edge>* adjacencyList;
    Array<Array<int>> incidencyMatrix;

    public:

    // inicjalizacja grafu
    // tworzy listę ora
    explicit Graph(int n, bool directed, int maxEdgeCount) {
        this->vertexCount = n;

        this->edgeCount = 0;
        this->directed = directed;

        //reprezentacja listowa
        adjacencyList = new SinglyLinkedList<Edge>[vertexCount];

        // reprezentacja macierzowa
        incidencyMatrix = Array<Array<int>>(vertexCount);

        for (int i = 0; i < vertexCount; i++) {
            incidencyMatrix[i] = Array<int>(maxEdgeCount);

            for (int j = 0; j < maxEdgeCount; j++) {
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
            adjacencyList[v].push(Edge(v, u, weight));
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

    int getVertexCount() {return vertexCount;}
    Vertex& getVertex(int index) { return vertices[index]; }

    int getEdgeCount() {return edgeCount;}

    template <typename T>
    SinglyLinkedList<Edge>& getAdjacencyList() {
        return *adjacencyList;
    }

};
#endif //GRAPH_H
