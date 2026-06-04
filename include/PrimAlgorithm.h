//
// Created by iraan on 02.05.2026.
//

#ifndef PRIMALGORITHM_H
#define PRIMALGORITHM_H
#include "Graph.h"
#include "QuickSort.h"

namespace PrimAlgorithm {

    //Metoda wstawia posortowanych według wag sąsiadów dla wybranej krawędzi
    void insertSorted(SinglyLinkedList<Edge>& queue, Edge edge) {

        //sprawdza czy jest początek listy
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


    //Implementacja algorytmu Prima
    //Znajduje minimalne drzewo rozpinające grafu MST
    Graph *prim(Graph& graph, SinglyLinkedList<Edge>& queue) {

        if (graph.isDirected()) {
            std::cout << "Graph is a directed graph." <<  std::endl;
            return nullptr;
        }

        int n = graph.getVertexCount();
        //tworzenie grafu mst do przechowywania wyniku
        auto* mst = new Graph(n, false, n-1);

        //Pętla główna
        while (queue.getSize() > 0) {
            //Pobieranie krawędzi o najmnieszej wadze
            Edge best = queue.getHead()->data;
            //usuwanie krawędzi z kolejki
            queue.popFront();

            //Sprawdzenie cyklu
            //Jeżeli wierzchołek krawędzi jest pokolorowany wraca na początek while
            if(graph.getVertex(best.to).colored) continue;


            //Dołączenie nowego wierzchołka do MST
            graph.getVertex(best.to).setColored(true);
            Vertex& vu = graph.getVertex(best.from);
            Vertex& vv = graph.getVertex(best.to);
            mst->addEdge(vu,vv, best.weight);


            //Dodawanie "sąsiadów" nowego wierzchołka
            SinglyLinkedList<Neighbor>::Node* adj = graph.getAdjacencyList(best.to);
            while (adj != nullptr) {
                //Sprawdzenie czy wierzchołki nie były już odwiedzone
                if (!graph.getVertex(adj->data.to.id).colored) {
                    insertSorted(queue, Edge(best.to, adj->data.to.id, adj->data.weight));
                }
                adj = adj->next;
            }
        }

        for (int i = 0; i < n; i++) {
            graph.getVertex(i).setColored(false);
        }

        if (mst->getEdgeCount() != n - 1) {
            delete mst;
            std::cout << "Graph is not connected!" << std::endl;
            return nullptr;
        }

        return mst;
    }
};
#endif //PRIMALGORITHM_H
