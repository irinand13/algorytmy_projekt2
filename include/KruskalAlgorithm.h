//
// Created by iraan on 02.05.2026.
//

#ifndef KRUSKALSALGORITHM_H
#define KRUSKALSALGORITHM_H
#include <list>

#include "Graph.h"
#include "Array.h"
#include "QuickSort.h"

namespace KruskalAlgorithm {
    //Funkcja zwracająca MST dla podanego grafu
    Graph *kruskal(Graph &graph, SinglyLinkedList<Edge> &edgeList) {

        if (graph.isDirected()) {
            std::cout << "Graph is a directed graph." << endl;
            return nullptr;
        }

        auto* mst = new Graph(graph.getVertexCount(), false, graph.getVertexCount()-1);

        SinglyLinkedList<Edge>::Node* current = edgeList.getHead();


        //inicjalizacja tablicy, zawierająca "kolory" dla każdej krawędzi
        int* colors = new int[graph.getVertexCount()];
        for (int i = 0; i < graph.getVertexCount(); i++) {
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
                Vertex vu = graph.getVertex(u);
                Vertex vv = graph.getVertex(v);

                //dodajemy krawędź do mst
                mst->addEdge(vu,vv, current->data.weight);

                //zmiana "kolorów" wierzchołków połączonych z 2
                for (int i = 0; i < graph.getVertexCount(); i++) {
                    if (colors[i] == colorV) {
                        colors[i] = colorU;
                    }
                }
            }
            current = current->next;
        }

        delete[] colors;

        if (mst->getEdgeCount() != graph.getVertexCount() - 1) {
            delete mst;
            std::cout << "Graph is not connected!" << endl;
            return nullptr;
        }
        return mst;
    }

};
#endif //KRUSKALSALGORITHM_H
