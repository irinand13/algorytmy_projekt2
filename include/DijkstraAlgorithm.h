//
// Created by iraan on 02.05.2026.
//

#ifndef DIJKSTRASALGORITHM_H
#define DIJKSTRASALGORITHM_H
#include "Graph.h"

namespace DijkstraAlgorithm {
    //Metoda wstawia posortowanych według wag sąsiadów dla wybranej krawędzi
    void insertSorted(SinglyLinkedList<Edge>& queue, Edge edge) {

        // sprawdza czy jest początek listy
        // czy waga krawędzi jest mniejsza od pierwszej warotści w kolejce
        //i dodaje je na początek kolejki
        if (queue.getHead() == nullptr || edge.weight < queue.getHead()->data.weight) {
            queue.pushFront(edge);
            return;
        }

        //Przesukiwanie miejsca gdzie wstawić krawędź, jeżeli waga jest większa od 1 elementu kolejki
        SinglyLinkedList<Edge>::Node* current = queue.getHead();
        while (current->next != nullptr && current->next->data.weight <= edge.weight) {
            current = current->next;
        }
        //wstawienie krawędzi oraz zmiana rozmiaru kolejki
        auto* newNode = new SinglyLinkedList<Edge>::Node(edge);
        newNode->next = current->next;
        current->next = newNode;
        queue.size++;
    }

    //algorytm Dijkstra
    Graph* dijkstraAlgorithm(Graph &graph, int from, int to) {

        if(!graph.isDirected()) {
            std::cout<<"Graph is not directed"<<std::endl;
            return nullptr;
        }

        int n = graph.getVertexCount();
        SinglyLinkedList<Edge> queue; //lists priorytetowa

        int* dist = new int[n]; //tablica odległości
        int* visited = new int[n]; //tablica poprzedników




        //ustawie odległości na maksimum i wierzchołki odwiedzone na -1
        for(int i = 0; i < n; i++) {
            dist[i] = INT_MAX;
            visited[i] = -1;
        }


        dist[from] = 0;
        insertSorted(queue, Edge(from, from, 0));

        //petla główna
        while(queue.getSize() > 0) {
            //pobiera krawędź z najlepszą odległością
            Edge best = queue.getHead()->data;
            queue.popFront();

            int u = best.to; //zapisuje indeks
            //sprawdza czy waga najmniejszej krawędzi jest większa od wagi z tablicy
            if (best.weight > dist[u]) continue;

            //szuka następną krawędź
            SinglyLinkedList<Neighbor>::Node* start = graph.getAdjacencyList(u);
            while (start != nullptr) {
                int v = start->data.to.id;
                int w = start->data.weight;

                //porównuje sumę wag wybranej krawędzi z wagą zapisanej w tablicy
                //przypisanego do tego samego wierzchołka
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    visited[v] = u;
                    insertSorted(queue, Edge(u, v, dist[v]));
                }
                start = start->next;
            }
        }

            if (dist[to] == INT_MAX) {
                std::cout << "No path from " << from << " to " << to << std::endl;
                delete[] dist;
                delete[] visited;
                return nullptr;
            }

        auto* path = new Graph(n, true, n - 1);
        //wypełnia graf
        int current = to;

        while (current != from) {

            int prev       = visited[current];
            int edgeWeight = dist[current] - dist[prev];
            Vertex& vPrev    = graph.getVertex(prev);
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
