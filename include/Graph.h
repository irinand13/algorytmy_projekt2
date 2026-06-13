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
        this->colored= colored;
    }

    void setColored(bool colored) {
        this->colored= colored;
    }

};

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
    // inicjalizacja grafu
    // tworzy listę ora
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
        delete[] vertices;
    }

    Graph(const Graph& graph) = delete;
    Graph& operator=(const Graph& graph) = delete;
    Graph(Graph&& graph) = delete;
    Graph& operator=(Graph&& graph) = delete;

    //Metoda dodawania nowej krawędzi
    // Dodaje krawiędź do listy oraz do macierzy incydencji
    void addEdge(Vertex& u, Vertex& v, int weight) {

        if (weight < 0) throw std::invalid_argument("weight cannot be negative");

        if (hasEdge(u.id, v.id)) throw std::invalid_argument("edge already exists");

        if (edgeCount >= maxEdgeCount) throw std::out_of_range("too many edges");

        adjacencyList[u.id].push({v, weight});

        if (directed) {
            incidencyMatrix[u.id][edgeCount] = 1;
            incidencyMatrix[v.id][edgeCount] = -1;
        } else {
            incidencyMatrix[u.id][edgeCount] = 1;
            incidencyMatrix[v.id][edgeCount] = 1;

            incidencyMatrix[v.id][edgeCount] = 1;
            incidencyMatrix[u.id][edgeCount] = 1;
        }

        totalWeight += weight;
        edgeCount++;

        if (!directed && !hasEdge(v.id, u.id)) {
            adjacencyList[v.id].push({u, weight});
        }
    }


    void readToEdgeList(SinglyLinkedList<Edge>& list) {
        for (int i = 0; i < vertexCount; i++) {

            SinglyLinkedList<Neighbor>::Node* current = adjacencyList[i].getHead();
            while (current != nullptr) {
                if (directed) {
                    int from = i;
                    int to = current->data.to.id;
                    int weight = current->data.weight;
                    list.push(Edge(from, to, weight));
                    current = current->next;
                } else {
                    if (i < current->data.to.id) {
                        int from = i;
                        int to = current->data.to.id;
                        int weight = current->data.weight;
                        list.push(Edge(from, to, weight));
                    }
                    current = current->next;
                }
            }
        }
    }



    int  getVertexCount() const {return vertexCount;}
    int getEdgeCount() const {return edgeCount;}
    Vertex& getVertex(int i) {return vertices[i];}
    bool isDirected () const {return directed;}
    int getTotalWeight() const {return totalWeight;}

    SinglyLinkedList<Neighbor>::Node* getAdjacencyList(int i) {
        return adjacencyList[i].getHead();
    }

    //Wypisuje listę sąsiedztwa dla grafu
    void print() {
        for (int i = 0; i < vertexCount; i++) {
            std::cout << i << ": ";
            SinglyLinkedList<Neighbor>::Node* current = adjacencyList[i].getHead();
            while (current != nullptr) {
                std::cout << "-> " << current->data.to.id
                          << " (w:" << current->data.weight << ") ";
                current = current->next;
            }
            std::cout << std::endl;
        }
    }

    //sprawdza czy krawędź już istnieje
    bool hasEdge(int from, int to) {
        SinglyLinkedList<Neighbor>::Node* current = adjacencyList[from].getHead();
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

        // sprawdza czy wszystkie wierzchołki są "pokolorowane"
        bool connected = true;
        for (int i = 0; i < vertexCount; i++) {
            if (!vertices[i].colored) {
                connected = false;
                break;
            }
        }

        //resetujemy kolory
        for (int i = 0; i < vertexCount; i++) vertices[i].colored = false;
        return connected;
    }


    //metoda DFS do przeszukiwania grafu
    void dfs(int vertex) {
        vertices[vertex].colored = true;
        SinglyLinkedList<Neighbor>::Node* current = adjacencyList[vertex].getHead();
        while (current != nullptr) {
            int neighbor = current->data.to.id;
            if (!vertices[neighbor].colored) {
                dfs(neighbor); //rekurencja
            }
            current = current->next;
        }
    }

};
#endif //GRAPH_H
