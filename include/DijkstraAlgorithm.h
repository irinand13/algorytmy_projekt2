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
    int *dijkstraAlgorithm(Graph &graph) {
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
        insertSorted(queue, Edge(0, 0, 0));

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
        return dist;
    }
};
#endif //DIJKSTRASALGORITHM_H
