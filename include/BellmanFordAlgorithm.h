//
// Created by iraan on 02.05.2026.
//

#ifndef BELLMANFORDSALGORITHM_H
#define BELLMANFORDSALGORITHM_H
#include "Graph.h"

namespace BellmanFordAlgorithm {
    int BellmanFord(Graph graph) {

        int n = graph.getVertexCount();
        SinglyLinkedList<Edge> queue; //lists priorytetowa

        int* dist = new int[n]; //tablica odległości
        int* visited = new int[n]; //tablica poprzedników

        if(!graph.isDirected()) return nullptr;


        //ustawie odległości na maksimum i wierzchołki odwiedzone na -1
        for(int i = 0; i < n; i++) {
            dist[i] = INT_MAX;
            visited[i] = -1;
        }

        //zaczyna od 0
        dist[0] = 0;

        //przechodzi przez wszystkie krawędzi
        for(int i = 0; i < n - 1; i++) {

            //przechodzi przez każdy wierzchołek
            for(int u = 0; u < n; u++) {
                if(dist[u] == INT_MAX) continue;

                SinglyLinkedList<Neighbor>::Node* start = graph.getAdjacencyList(u);
                while (start != nullptr) {
                    int v = start->data.to.id;
                    int w = start->data.weight;

                    //porównuje sumę wag wybranej krawędzi z wagą zapisanej w tablicy
                    //przypisanego do tego samego wierzchołka
                    if (dist[u] + w < dist[v]) {
                        dist[v] = dist[u] + w;
                        visited[v] = u;
                    }
                    start = start->next;
                }

            }
        }

    }
};
#endif //BELLMANFORDSALGORITHM_H
