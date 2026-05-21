//
// Created by iraan on 02.05.2026.
//

#ifndef KRUSKALSALGORITHM_H
#define KRUSKALSALGORITHM_H
#include "Graph.h"
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

    template<class T>
    inline SinglyLinkedList<Edge> sortEdgeList(Graph& graph) {
        auto sortedEdgeList = graph.getAdjacencyList<Edge>();
        quickSort(sortedEdgeList);

        return sortedEdgeList;
    }


};
#endif //KRUSKALSALGORITHM_H
