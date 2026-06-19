//
// Created by iraan on 02.05.2026.
//

#ifndef KRUSKALSALGORITHM_H
#define KRUSKALSALGORITHM_H
#include <iostream>

#include "Graph.h"
#include "Array.h"
#include "QuickSort.h"

namespace KruskalAlgorithm {
    //Algorytm Kruskala
    Graph *kruskal(int vertexCount, SinglyLinkedList<Edge> &edgeList) {

        auto* mst = new Graph(vertexCount, false, vertexCount - 1);

        QuickSort::quickSort(edgeList);
        SinglyLinkedList<Edge>::Node* current = edgeList.getHead();


        //inicjalizacja tablicy, zawierająca kolory dla każdej krawędzi
        int* colors = new int[vertexCount];
        for (int i = 0; i < vertexCount; i++) {
            colors[i] = i;
        }

        while (current) {
            //pobiera indeksy wierzchołków należących do danej krawędzi
            int u = current->data.from;
            int v = current->data.to;

            //szuka "kolor" w tablicy dla odpowiednich indeksów
            int colorU = colors[u];
            int colorV = colors[v];


            //Jeżeli "kolory" są różne, zmieniamy kolor 2 wierzchołka
            if (colorU != colorV) {
                Vertex& vu = mst->getVertex(u);
                Vertex& vv = mst->getVertex(v);

                //dodajemy krawędź do mst
                mst->addEdge(vu, vv, current->data.weight);

                //zmiana "kolorów" wierzchołków połączonych z 2
                for (int i = 0; i < vertexCount; i++) {
                    if (colors[i] == colorV) {
                        colors[i] = colorU;
                    }
                }
            }
            current = current->next;
        }

        delete[] colors;

        if (mst->getEdgeCount() != vertexCount - 1) {
            delete mst;
            std::cout << "Graph is not connected!" << std::endl;
            return nullptr;
        }
        return mst;
    }

};
#endif //KRUSKALSALGORITHM_H