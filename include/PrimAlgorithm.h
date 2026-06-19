//
// Created by iraan on 02.05.2026.
//

#ifndef PRIMALGORITHM_H
#define PRIMALGORITHM_H
#include "Graph.h"
#include "QuickSort.h"
#include <iostream>

namespace PrimAlgorithm {

    //Metoda wstawia posortowanych według wag sąsiadów dla wybranej krawędzi
    void insertSorted(SinglyLinkedList<Edge>& queue, Edge edge) {

        // sprawdza czy jest początek listy
        // czy waga krawędzi jest mniejsza od pierwszej warotści w kolejce
        //i dodaje je na początek kolejki
        if (queue.getHead() == nullptr || edge.weight < queue.getHead()->data.weight) {
            queue.pushFront(edge);
            return;
        }

        //przesukiwanie miejsca gdzie wstawić krawędź
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


    //Implementacja algorytmu Prima
    Graph *prim(int vertexCount, SinglyLinkedList<Edge>& allEdges) {

        // Tablica do śledzenia pokolorowanych wierzchołków
        bool* colored = new bool[vertexCount];
        for (int i = 0; i < vertexCount; i++) {
            colored[i] = false;
        }

        SinglyLinkedList<Edge> queue;
        //tworzenie grafu mst do przechowywania wyniku
        auto* mst = new Graph(vertexCount, false, vertexCount - 1);


        //zaczyna od wierzchołka 0
        colored[0] = true;

        // Przeszukuje przekazaną listę krawędzi w poszukiwaniu sąsiadów wierzchołka
        SinglyLinkedList<Edge>::Node* start = allEdges.getHead();
        while (start != nullptr) {
            if (start->data.from == 0) {
                insertSorted(queue, start->data);
            } else if (start->data.to == 0) {
                insertSorted(queue, Edge(0, start->data.from, start->data.weight));
            }
            start = start->next;
        }

        //Pętla główna
        while (queue.getSize() > 0) {
            //Pobieranie krawędzi o najmnieszej wadze
            Edge best = queue.getHead()->data;
            //usuwanie krawędzi z kolejki
            queue.popFront();

            //Sprawdzenie cyklu
            //Jeżeli wierzchołek krawędzi jest pokolorowany wraca na początek while
            if (colored[best.to]) continue;


            //Dołączenie nowego wierzchołka do MST
            colored[best.to] = true;
            Vertex& vu = mst->getVertex(best.from);
            Vertex& vv = mst->getVertex(best.to);
            mst->addEdge(vu, vv, best.weight);


            //Dodawanie "sąsiadów" nowego wierzchołka z przekazanej listy krawędzi
            SinglyLinkedList<Edge>::Node* adj = allEdges.getHead();
            while (adj != nullptr) {
                int u = adj->data.from;
                int v = adj->data.to;
                int w = adj->data.weight;

                //Sprawdza czy wierzchołki nie były już odwiedzone
                if (u == best.to && !colored[v]) {
                    insertSorted(queue, Edge(u, v, w));
                } else if (v == best.to && !colored[u]) {
                    insertSorted(queue, Edge(v, u, w));
                }
                adj = adj->next;
            }
        }

        int finalEdgeCount = mst->getEdgeCount();
        delete[] colored; // Czyszczenie pamięci tablicy

        if (finalEdgeCount != vertexCount - 1) {
            delete mst;
            std::cout << "Graph is not connected!" << std::endl;
            return nullptr;
        }

        return mst;
    }
};
#endif //PRIMALGORITHM_H