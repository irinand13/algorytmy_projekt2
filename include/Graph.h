//
// Created by iraan on 02.05.2026.
//

#ifndef GRAPH_H
#define GRAPH_H
#include "Array.h"
#include "SinglyLinkedList.h"
#include <iostream>
#include <stdexcept>

//Reprezentacja krawędzi
struct Edge {
    int from;
    int to;
    int weight;

    Edge() : from(0), to(0), weight(0) {}

    Edge(int from, int to, int weight) {
        this->from = from;
        this->to = to;
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

    Vertex() {
        id = 0;
        colored = false;
    }

    Vertex(int id, bool colored) {
        this->id = id;
        this->colored = colored;
    }

    void setColored(bool colored) {
        this->colored = colored;
    }
};

//struktura reprezentująca sąsiada
struct Neighbor {
    Vertex to;
    int weight;

    Neighbor() : to(), weight(0) {}

    Neighbor(Vertex to, int weight) {
        this->to = to;
        this->weight = weight;
    }
};

//Reprezentacja grafu
class Graph {
    int vertexCount;
    int edgeCount;
    int maxEdgeCount;
    int totalWeight;
    bool directed;

    Vertex *vertices;
    SinglyLinkedList<Neighbor>* adjacencyList;
    Array<Array<int>> incidencyMatrix;

public:
    explicit Graph(int n, bool directed, int maxEdgeCount) {
        this->vertexCount = n;
        this->maxEdgeCount = maxEdgeCount;
        this->edgeCount = 0;
        this->totalWeight = 0;
        this->directed = directed;

        vertices = new Vertex[vertexCount];
        for (int i = 0; i < vertexCount; i++) {
            vertices[i] = Vertex(i, false);
        }

        //reprezentacje grafu
        adjacencyList = new SinglyLinkedList<Neighbor>[vertexCount]; //lista sąsiedztwa
        incidencyMatrix = Array<Array<int>>(vertexCount); //macierz incydencji

        for (int i = 0; i < vertexCount; i++) {
            incidencyMatrix[i] = Array<int>(maxEdgeCount);
            for (int j = 0; j < maxEdgeCount; j++) {
                incidencyMatrix[i][j] = 0;
            }
        }
    }

    ~Graph() {
        delete[] adjacencyList;
        delete[] vertices;
    }

    Graph(const Graph& graph) = delete;
    Graph& operator=(const Graph& graph) = delete;
    Graph(Graph&& graph) = delete;
    Graph& operator=(Graph&& graph) = delete;

    //dodaje krawędź do grafu
    void addEdge(Vertex& u, Vertex& v, int weight) {
        if(weight <= 0) throw std::invalid_argument("Graph::addEdge(): weight must be positive");
        if (hasEdge(u.id, v.id)) throw std::invalid_argument("edge already exists");
        if (edgeCount >= maxEdgeCount) throw std::out_of_range("too many edges");

        //dodanie do listy sąsiedztwa
        adjacencyList[u.id].push({v, weight});

        //dodanie do macierzy incydencji
        if (directed) {
            incidencyMatrix[u.id][edgeCount] = weight;       // Wychodząca: dodatnia waga
            incidencyMatrix[v.id][edgeCount] = -weight;      // Wchodząca: ujemna waga
        } else {
            incidencyMatrix[u.id][edgeCount] = weight;       // Nieskierowana: obie dodatnie
            incidencyMatrix[v.id][edgeCount] = weight;
        }

        totalWeight += weight;
        edgeCount++;

        if (!directed && !hasEdge(v.id, u.id)) {
            adjacencyList[v.id].push({u, weight});
        }
    }

    //odczytuje z listy sąsiedztwa do listy krawędzi
    void readAdjacencyToEdgeList(SinglyLinkedList<Edge>& list) {
        for (int i = 0; i < vertexCount; i++) {
            typename SinglyLinkedList<Neighbor>::Node* current = adjacencyList[i].getHead();
            while (current != nullptr) {
                if (directed) {
                    list.push(Edge(i, current->data.to.id, current->data.weight));
                } else {
                    // Dla nieskierowanego bierzemy krawędź tylko raz (zapobiega duplikatom)
                    if (i < current->data.to.id) {
                        list.push(Edge(i, current->data.to.id, current->data.weight));
                    }
                }
                current = current->next;
            }
        }
    }

  //odczytuje z macierzy incydencji do listy krawędzi
    void readMatrixToEdgeList(SinglyLinkedList<Edge>& list) {
        // Przechodzimy po kolumnach
        for (int col = 0; col < edgeCount; col++) {
            int from = -1;
            int to = -1;
            int weight = 0;

            if (directed) {
                for (int row = 0; row < vertexCount; row++) {
                    int val = incidencyMatrix[row][col];
                    if (val > 0) {
                        from = row;
                        weight = val; // waga jest dodatnia przy wierzchołku startowym
                    } else if (val < 0) {
                        to = row;
                    }
                }
                if (from != -1 && to != -1) {
                    list.push(Edge(from, to, weight));
                }
            } else {
                // dla grafu nieskierowanego szukamy dwóch wierzchołków z tą samą wagą
                for (int row = 0; row < vertexCount; row++) {
                    int val = incidencyMatrix[row][col];
                    if (val > 0) {
                        if (from == -1) {
                            from = row;
                            weight = val;
                        } else {
                            to = row;
                        }
                    }
                }
                if (from != -1 && to != -1) {
                    list.push(Edge(from, to, weight));
                }
            }
        }
    }

    int getVertexCount() const { return vertexCount; }
    int getEdgeCount() const { return edgeCount; }
    Vertex& getVertex(int i) { return vertices[i]; }
    bool isDirected() const { return directed; }
    int getTotalWeight() const { return totalWeight; }

    typename SinglyLinkedList<Neighbor>::Node* getAdjacencyList(int i) {
        return adjacencyList[i].getHead();
    }

    //wypisuje listę sąsiedztwa
    void print() {
        for (int i = 0; i < vertexCount; i++) {
            std::cout << i << ": ";
            typename SinglyLinkedList<Neighbor>::Node* current = adjacencyList[i].getHead();
            while (current != nullptr) {
                std::cout << "-> " << current->data.to.id
                          << " (w:" << current->data.weight << ") ";
                current = current->next;
            }
            std::cout << std::endl;
        }
    }

    //sprawdza czy graf ma już krawędź pomiędzy podanymi wierzchołkami
    bool hasEdge(int from, int to) {
        typename SinglyLinkedList<Neighbor>::Node* current = adjacencyList[from].getHead();
        while (current != nullptr) {
            if (current->data.to.id == to) return true;
            current = current->next;
        }
        return false;
    }

    //sprawdza czy graf jest spójny
    bool isConnected() {
        for (int i = 0; i < vertexCount; i++) vertices[i].colored = false;
        dfs(0);
        bool connected = true;
        for (int i = 0; i < vertexCount; i++) {
            if (!vertices[i].colored) {
                connected = false;
                break;
            }
        }
        for (int i = 0; i < vertexCount; i++) vertices[i].colored = false;
        return connected;
    }

    // pomocnicza funkcja dfs, która przeszukuje graf w głąb
    void dfs(int vertex) {
        vertices[vertex].colored = true;
        typename SinglyLinkedList<Neighbor>::Node* current = adjacencyList[vertex].getHead();
        while (current != nullptr) {
            int neighbor = current->data.to.id;
            if (!vertices[neighbor].colored) {
                dfs(neighbor);
            }
            current = current->next;
        }
    }

    //zwraca wartość z macierzy incydencji
    int getMatrixValue(int row, int col) {
        return incidencyMatrix[row][col];
    }
};

#endif //GRAPH_H
