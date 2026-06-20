//
// Created by iraan on 02.05.2026.
//

#ifndef BELLMANFORDSALGORITHM_H
#define BELLMANFORDSALGORITHM_H
#include "Graph.h"
#include <climits>
#include <iostream>

namespace BellmanFordAlgorithm {
    // Imlementacja algorytmu Bellmana-Forda
    Graph* bellmanFord(Graph &graph, int from, int to, bool useMatrix) {
        int n = graph.getVertexCount();

        int* dist = new int[n]; // tablica odległości
        int* visited = new int[n]; // tablica poprzedników

        // ustawia odległości na maksimum i wierzchołków odwiedzonych na -1
        for(int i = 0; i < n; i++) {
            dist[i] = INT_MAX;
            visited[i] = -1;
        }

        dist[from] = 0;

        //relaksacja w zależności od wybranej struktury
        for(int i = 0; i < n - 1; i++) {
            
            if (useMatrix) {
                // reklasacja dla macierzy
                int edgeCount = graph.getEdgeCount();
                // przeechodzi przez koluny krawędzi
                for (int e = 0; e < edgeCount; e++) {
                    int u = -1, v = -1;
                    int w = 0;

                    for (int row = 0; row < n; row++) {
                        int val = graph.getMatrixValue(row, e);
                        if (val > 0) {
                            u = row;
                            w = val;
                        } else if (val < 0) {
                            v = row;
                        }
                    }

                    // relaksacja krawędzi
                    if (u != -1 && v != -1 && dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                        dist[v] = dist[u] + w;
                        visited[v] = u;
                    }
                }
            } else {
                //relaksacja dla listy sąsiedztwa
                for (int u = 0; u < n; u++) {
                    SinglyLinkedList<Neighbor>::Node* start = graph.getAdjacencyList(u);
                    while (start != nullptr) {
                        int v = start->data.to.id;
                        int w = start->data.weight;

                        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                            dist[v] = dist[u] + w;
                            visited[v] = u;
                        }
                        start = start->next;
                    }
                }
            }
        }

        //jeżeli wartość do wiezrchołku końcowego jest nieskończonnością, to nie ścieżki do tego wierzchołka
        if (dist[to] == INT_MAX) {
            delete[] dist;
            delete[] visited;
            return nullptr;
        }

        auto* path = new Graph(n, true, n - 1);

        //odtwaranie ścieżki
        int current = to;
        while (current != from) {
            int prev = visited[current];
            Vertex& vPrev = graph.getVertex(prev);
            Vertex& vCurrent = graph.getVertex(current);
            path->addEdge(vPrev, vCurrent, dist[current] - dist[prev]);
            current = prev;
        }

        delete[] dist;
        delete[] visited;
        return path;
    }
};
#endif //BELLMANFORDSALGORITHM_H