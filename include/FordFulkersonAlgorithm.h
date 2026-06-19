//
// Created by iraan on 02.05.2026.
//

#ifndef FORDFULKERSONALGORITHM_H
#define FORDFULKERSONALGORITHM_H

#include <iostream>
#include <climits>
#include <algorithm>
#include <cmath>
#include "Graph.h"

namespace FordFulkersonAlgorithm {

    //wykorzysta DFS do przeszukiwania ścieżki od żródła do końca
    bool dfs(int** residual, int n, int source, int sink, int* parent, bool* visited) {
        visited[source] = true;
        if (source == sink) return true;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && residual[source][v] > 0) {
                parent[v] = source;
                if (dfs(residual, n, v, sink, parent, visited))
                    return true;
            }
        }
        return false;
    }

    // Implementacja algorytmu Forda-Fulkersona
    Graph* fordFulkerson(Graph& graph, int source, int sink, int& maxFlow, bool useMatrix) {
        int n = graph.getVertexCount();
        maxFlow = 0;

        // dynamiczna alokacja sieci rezydualnej
        int** residual = new int*[n];
        int** capacities = new int*[n];
        for (int i = 0; i < n; i++) {
            residual[i] = new int[n]();
            capacities[i] = new int[n]();
        }

        //przepisanie wag na podstawie wybranej struktury
        if (useMatrix) {
            int edgeCount = graph.getEdgeCount();

            // przechodzi przez kolumny w macierzy incydencji
            for (int e = 0; e < edgeCount; e++) {
                int u = -1, v = -1;
                int weight = 0;

                for (int row = 0; row < n; row++) {
                    int val = graph.getMatrixValue(row, e);
                    if (val > 0) {
                        u = row;
                        weight = val;
                    } else if (val < 0) {
                        v = row;
                    }
                }

                // jeśli poprawnie zidentyfikowano krawędź skierowaną
                if (u != -1 && v != -1) {
                    residual[u][v] += weight;
                    capacities[u][v] += weight;
                }
            }
        } else {
            // odczyt z listy sąsiedztwa
            for (int u = 0; u < n; u++) {
                SinglyLinkedList<Neighbor>::Node* start = graph.getAdjacencyList(u);
                while (start != nullptr) {
                    int v = start->data.to.id;
                    int w = start->data.weight;
                    residual[u][v] += w;
                    capacities[u][v] += w;
                    start = start->next;
                }
            }
        }

        int* parent = new int[n];
        bool* visited = new bool[n];

        // Główna pętla
        while (true) {
            for (int i = 0; i < n; i++) {
                parent[i] = -1;
                visited[i] = false;
            }

            if (!dfs(residual, n, source, sink, parent, visited)) break;

            // Znajduje wąskie gardło
            int bottleneck = INT_MAX;
            int v = sink;
            while (v != source) {
                int u = parent[v];
                bottleneck = std::min(bottleneck, residual[u][v]);
                v = u;
            }

            // Aktualizuje sieć rezydualną
            v = sink;
            while (v != source) {
                int u = parent[v];
                residual[u][v] -= bottleneck;
                residual[v][u] += bottleneck;
                v = u;
            }

            maxFlow += bottleneck;
        }

        // Generowanie grafu wynikowego
        int maxEdges = n * (n - 1);
        auto* flowGraph = new Graph(n, true, maxEdges);

        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                if (capacities[u][v] > 0) {
                    int flow = capacities[u][v] - residual[u][v];
                    if (flow > 0) {
                        Vertex fromVertex = graph.getVertex(u);
                        Vertex toVertex = graph.getVertex(v);
                        flowGraph->addEdge(fromVertex, toVertex, flow);
                    }
                }
            }
        }

        // Zwolnienie pamięci
        for (int i = 0; i < n; i++) {
            delete[] residual[i];
            delete[] capacities[i];
        }
        delete[] residual;
        delete[] capacities;
        delete[] parent;
        delete[] visited;

        return flowGraph;
    }
};

#endif // FORDFULKERSONALGORITHM_H