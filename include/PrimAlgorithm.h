//
// Created by iraan on 02.05.2026.
//

#ifndef PRIMALGORITHM_H
#define PRIMALGORITHM_H
#include "Graph.h"
#include "QuickSort.h"
using namespace std;

namespace PrimAlgorithm {

    void insertSorted(SinglyLinkedList<Edge>& queue, Edge edge) {
        if (queue.getHead() == nullptr || edge.weight < queue.getHead()->data.weight) {
            queue.pushFront(edge);
            return;
        }
        SinglyLinkedList<Edge>::Node* current = queue.getHead();
        while (current->next != nullptr && current->next->data.weight <= edge.weight) {
            current = current->next;
        }
        auto* newNode = new SinglyLinkedList<Edge>::Node(edge);
        newNode->next = current->next;
        current->next = newNode;
        queue.size++;
    }

    template<class T>
    Graph *prim(Graph& graph) {
        int n = graph.getVertexCount();
        auto* mst = new Graph(n, false, n-1);

        SinglyLinkedList<Edge> queue;
        graph.getVertex(0).setColored(true);
        SinglyLinkedList<Neighbor>::Node* start = graph.getAdjacencyList(0);

        while (start != nullptr) {
            insertSorted(queue, Edge(0, start->data.to.id, start->data.weight));
            start = start->next;
        }


        while (queue.getSize() > 0) {
            Edge best = queue.getHead()->data;
            queue.popFront();

            if(graph.getVertex(best.to).colored) continue;

            graph.getVertex(best.to).setColored(true); //
            Vertex& vu = graph.getVertex(best.from);
            Vertex& vv = graph.getVertex(best.to);
            mst->addEdge(vu,vv, best.weight);


            SinglyLinkedList<Neighbor>::Node* adj = graph.getAdjacencyList(best.to);
            while (adj != nullptr) {
                if (!graph.getVertex(adj->data.to.id).colored) {
                    insertSorted(queue, Edge(best.to, adj->data.to.id, adj->data.weight));
                }
                adj = adj->next;
            }
        }
        return mst;
    }
};
#endif //PRIMALGORITHM_H
