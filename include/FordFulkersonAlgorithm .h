//
// Created by iraan on 02.05.2026.
//

#ifndef FORDFULKERSONALGORITHM_H
#define FORDFULKERSONALGORITHM_H
#include "Graph.h"

namespace FordFulkersonAlgorithm {

    //wykorzysta DFS do przeszukiwania ścieżki od żródła do końca
    bool dfs(Graph& graph, int** residual, int n, int source, int sink, int* parent) {
        graph.getVertex(source).setColored(true);

        if (source == sink) return true;

        for (int v = 0; v < n; v++) {
            if (!graph.getVertex(v).colored && residual[source][v] > 0) {
                parent[v] = source;
                if (dfs(graph, residual, n, v, sink, parent))
                    return true;
            }
        }
        return false;
    }

    int fordFulkerson(Graph& graph, int source, int sink) {
        int n = graph.getVertexCount();

        if (!graph.isDirected()) {
            std::cout<<"Graph is not a directed graph."<<std::endl;
            return 0;
        }

        // macierz przepustowości
        int** residual = new int*[n];
        for (int i = 0; i < n; i++) {
            residual[i] = new int[n];
            for (int j = 0; j < n; j++)
                residual[i][j] = 0;
        }

        // wypełnia macierz wagami z grafu
        for (int u = 0; u < n; u++) {
            SinglyLinkedList<Neighbor>::Node* start = graph.getAdjacencyList(u);
            while (start != nullptr) {
                int v = start->data.to.id;
                int w = start->data.weight;
                residual[u][v] += w;
                start = start->next;
            }
        }

        int* parent = new int[n];
        int maxFlow = 0;

        while (true) {
            // reset kolorów przed każdym DFS
            for (int i = 0; i < n; i++) {
                parent[i] = -1;
                graph.getVertex(i).setColored(false);
            }

            if (!dfs(graph, residual, n, source, sink, parent)) break;

            // wąskie gardło
            int bottleneck = INT_MAX;
            int v = sink;
            while (v != source) {
                int u = parent[v];
                bottleneck = std::min(bottleneck, residual[u][v]);
                v = u;
            }

            // aktualizuj przepustowość
            v = sink;
            while (v != source) {
                int u = parent[v];
                residual[u][v] -= bottleneck;
                residual[v][u] += bottleneck;
                v = u;
            }

            maxFlow += bottleneck;
        }

        // reset kolorów na końcu
        for (int i = 0; i < n; i++)
            graph.getVertex(i).setColored(false);

        for (int i = 0; i < n; i++)
            delete[] residual[i];
        delete[] residual;
        delete[] parent;

        return maxFlow;
    }
};
#endif //FORDFULKERSONALGORITHM_H