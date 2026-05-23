//
// Created by iraan on 02.05.2026.
//

#ifndef KRUSKALSALGORITHM_H
#define KRUSKALSALGORITHM_H
#include "Graph.h"
#include "Array.h"
using namespace std;

namespace KruskalAlgorithm {

    //Rekurencja do sortowania szybkiego
    //dzieli listę na 3 części(mniejsze, równe i większe od piwota)
    // wstawia wartości w odpowiednie miejsce
    template<class T>
    typename SinglyLinkedList<T>::Node* quickSortRecursive(typename SinglyLinkedList<T>::Node* head, int currentSize) {
        using Node = typename SinglyLinkedList<T>::Node;

        if (!head || !head->next) return head;

        Node* pivotNode = head;

        for (int i = 0; i < currentSize / 2; i++) pivotNode = pivotNode->next;

        T pivotValue = pivotNode->data;

        Node *lessHead = nullptr, *equalHead = nullptr, *greaterHead = nullptr;
        int lessSize = 0, greaterSize = 0;

        Node* current = head;
        while (current) {
            Node* next = current->next;
            current->next = nullptr;

            if ((current->data) < pivotValue) {
                current->next = lessHead;
                lessHead = current;
                lessSize++;
            } else if (current->data > pivotValue) {
                current->next = greaterHead;
                greaterHead = current;
                greaterSize++;
            } else {
                current->next = equalHead;
                equalHead = current;
            }
            current = next;
        }

        lessHead = quickSortRecursive<T>(lessHead, lessSize);
        greaterHead = quickSortRecursive<T>(greaterHead, greaterSize);


        Node* newHead = nullptr;
        Node* tail = nullptr;


        auto append = [&](Node* section) {
            if (!section) return;
            if (!newHead) {
                newHead = section;
            } else {
                tail->next = section;
            }
            tail = section;
            while (tail->next) tail = tail->next;
        };

        append(lessHead);
        append(equalHead);
        append(greaterHead);

        return newHead;
    }


    //Sortowanie szybkie
    //wywoła metodę rekurencyjną i ustawia nową głowę
    template<class T>
    void quickSort(SinglyLinkedList<T>& list) {
        if (list.getSize() <= 1) return;

        list.head = quickSortRecursive<T>(list.head, list.getSize());
    }



    //Funkcja zwracająca MST dla podanego grafu
    template<class T>
    Graph *findMST(Graph &graph) {
        auto sortedEdgeList = SinglyLinkedList<Edge>();
        graph.readToEdgeList(sortedEdgeList);  // odczytywanie krawędzi oraz wag do listy krawędzi
        quickSort(sortedEdgeList); //sortowanie krawędzi według wag rosnąco

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
