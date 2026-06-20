//
// Created by iraan on 02.05.2026.
//

#ifndef DIJKSTRASALGORITHM_H
#define DIJKSTRASALGORITHM_H
#include "Graph.h"
#include <iostream>
#include <climits>

namespace DijkstraAlgorithm {
    // Metoda wstawia posortowanych według wag sąsiadów dla wybranej krawędzi
    void insertSorted(SinglyLinkedList<Edge>& queue, Edge edge) {
        // sprawdza czy jest początek listy lub czy waga krawędzi jest mniejsza od pierwszej wartości w kolejce
        if (queue.getHead() == nullptr || edge.weight < queue.getHead()->data.weight) {
            queue.pushFront(edge);
            return;
        }

        // przeszukiwanie miejsca gdzie wstawić krawędź
        SinglyLinkedList<Edge>::Node* current = queue.getHead();
        while (current->next != nullptr && current->next->data.weight <= edge.weight) {
            current = current->next;
        }

        // wstawienie krawędzi
        auto* newNode = new SinglyLinkedList<Edge>::Node(edge);
        newNode->next = current->next;
        current->next = newNode;
        queue.size++;
    }

    // Implementacja algorytmu  Dijkstra
    Graph* dijkstra(Graph &graph, int from, int to, bool useMatrix) {
        if(!graph.isDirected()) {
            std::cout << "Graph is not directed" << std::endl;
            return nullptr;
        }

        int n = graph.getVertexCount();
        SinglyLinkedList<Edge> queue; // lista priorytetowa

        int* dist = new int[n]; // tablica odległości
        int* visited = new int[n]; // tablica poprzedników

        // ustawienie odległości na maksimum i wierzchołki odwiedzone na -1
        for(int i = 0; i < n; i++) {
            dist[i] = INT_MAX;
            visited[i] = -1;
        }

        dist[from] = 0;
        insertSorted(queue, Edge(from, from, 0));

        // pętla główna
        while(queue.getSize() > 0) {
            // pobiera krawędź z najlepszą odległością
            Edge best = queue.getHead()->data;
            queue.popFront();

            int u = best.to; // aktualny wierzchołek

            // sprawdza czy waga najmniejszej krawędzi jest większa od wagi z tablicy
            if (best.weight > dist[u]) continue;

            if (useMatrix) {
                int edgeCount = graph.getEdgeCount();
                // przeszukujemy kolumny macierzy incydencji w poszukiwaniu krawędzi wychodzących z 'u'
                for (int e = 0; e < edgeCount; e++) {
                    int valFrom = graph.getMatrixValue(u, e);

                    if (valFrom > 0) {
                        int w = valFrom;
                        int v = -1;

                        //szuka wierzchołka końcowego
                        for (int row = 0; row < n; row++) {
                            if (graph.getMatrixValue(row, e) < 0) {
                                v = row;
                                break;
                            }
                        }

                        // relaksacja krawędzi
                        if (v != -1 && dist[u] + w < dist[v]) {
                            dist[v] = dist[u] + w;
                            visited[v] = u;
                            insertSorted(queue, Edge(u, v, dist[v]));
                        }
                    }
                }
            } else {
                // odczyt z listy sąsiedztwa
                SinglyLinkedList<Neighbor>::Node* start = graph.getAdjacencyList(u);
                while (start != nullptr) {
                    int v = start->data.to.id;
                    int w = start->data.weight;

                    if (dist[u] + w < dist[v]) {
                        dist[v] = dist[u] + w;
                        visited[v] = u;
                        insertSorted(queue, Edge(u, v, dist[v]));
                    }
                    start = start->next;
                }
            }
        }

        //jeżeli wartość do wiezrchołku końcowego jest nieskończonnością, to nie ścieżki do tego wierzchołka
        if (dist[to] == INT_MAX) {
            std::cout << "No path from " << from << " to " << to << std::endl;
            delete[] dist;
            delete[] visited;
            return nullptr;
        }

        auto* path = new Graph(n, true, n - 1);
        int current = to;


        //odtwarzanie ścieżki
        while (current != from) {
            int prev = visited[current];
            int edgeWeight = dist[current] - dist[prev];
            Vertex& vPrev = graph.getVertex(prev);
            Vertex& vCurrent = graph.getVertex(current);
            path->addEdge(vPrev, vCurrent, edgeWeight);
            current = prev;
        }

        delete[] dist;
        delete[] visited;
        return path;
    }
};
#endif //DIJKSTRASALGORITHM_H