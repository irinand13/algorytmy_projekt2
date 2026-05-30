//
// Created by iraan on 02.05.2026.
//

#ifndef KRUSKALSALGORITHM_H
#define KRUSKALSALGORITHM_H
#include "Graph.h"
#include "Array.h"
#include "QuickSort.h"
using namespace std;

namespace KruskalAlgorithm {

    //Funkcja zwracająca MST dla podanego grafu
    template<class T>
    Graph *kruskal(Graph &graph) {
        auto sortedEdgeList = SinglyLinkedList<Edge>();
        graph.readToEdgeList(sortedEdgeList);  // odczytywanie krawędzi oraz wag do listy krawędzi
        QuickSort::quickSort(sortedEdgeList); //sortowanie krawędzi według wag rosnąco

        auto* mst = new Graph(graph.getVertexCount(), false, graph.getVertexCount()-1);

        SinglyLinkedList<Edge>::Node* current = sortedEdgeList.getHead();


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
        return mst;
    }

};
#endif //KRUSKALSALGORITHM_H
