//
// Created by iraan on 02.05.2026.
//

#ifndef GRAPH_H
#define GRAPH_H
#include "Array.h"
#include "SinglyLinkedList.h"

//Reprezentacja krawędzi



//Reprezentacja wierzchołka
struct Vertex {
    int id;
    bool colored;

    Vertex() : id(0), colored(false) {}

    Vertex(int id, bool colored) {
        this->id = id;
        this->colored = colored;
    }

    void setColored() {
        this->colored = true;

    }

};

struct Neighbor {
    Vertex to;
    int weight;
};

//Reprezentacja grafu
class Graph {
    int vertexCount;
    int edgeCount;
    int maxEdgeCount;
    bool directed;


    SinglyLinkedList<Neighbor>* adjacencyList;
    Array<Array<int>> incidencyMatrix;


    public:
    // inicjalizacja grafu
    // tworzy listę ora
    explicit Graph(int n, bool directed, int maxEdgeCount) {
        this->vertexCount = n;
        this->maxEdgeCount = maxEdgeCount;
        this->edgeCount = 0;
        this->directed = directed;

        //reprezentacja listowa
        adjacencyList = new SinglyLinkedList<Neighbor>[vertexCount];

        // reprezentacja macierzowa
        incidencyMatrix = Array<Array<int>>(vertexCount);

        for (int i = 0; i < vertexCount; i++) {
            incidencyMatrix[i] = Array<int>(maxEdgeCount);

            for (int j = 0; j < maxEdgeCount; j++) {
                incidencyMatrix[i][j] = 0;
            }
        }
    }


    ~Graph() {
        delete[] adjacencyList;
    }
    Graph(const Graph& graph) = delete;
    Graph& operator=(const Graph& graph) = delete;
    Graph(Graph&& graph) = delete;
    Graph& operator=(Graph&& graph) = delete;

    //Metoda dodawania nowej krawędzi
    // Dodaje krawiędź do listy oraz do macierzy incydencji
    void addEdge(Vertex& u, Vertex& v, int weight) {

        if (edgeCount >= maxEdgeCount) {
            throw std::out_of_range("too many edges");
        }

        if (weight < 0) throw std::invalid_argument("weight cannot be negative");

        adjacencyList[u.id].push({v, weight});

        if (!directed)
            adjacencyList[v.id].push({u, weight});

        if (directed) {
            incidencyMatrix[u.id][edgeCount] = 1;
            incidencyMatrix[v.id][edgeCount] = -1;
        } else {
            incidencyMatrix[u.id][edgeCount] = 1;
            incidencyMatrix[v.id][edgeCount] = 1;
        }

        edgeCount++;
    }

    int getVertexCount() {return vertexCount;}
    int getEdgeCount() {return edgeCount;}

};
#endif //GRAPH_H
