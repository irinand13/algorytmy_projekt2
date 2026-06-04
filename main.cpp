#include <iostream>
#include <GenerateGraph.h>

#include "KruskalAlgorithm.h"
#include "PrimAlgorithm.h"
using namespace std;
int main() {
    srand(time(nullptr));
    Graph* graph = GenerateGraph::generateGraph(10,false, 50);


    SinglyLinkedList<Edge> queue;
    SinglyLinkedList<Neighbor>::Node* start = graph->getAdjacencyList(0);
    while (start != nullptr) {
        PrimAlgorithm::insertSorted(queue, Edge(0, start->data.to.id, start->data.weight));
        start = start->next;
    }
    graph->print();
    graph->getVertex(0).setColored(true);
    Graph* mst = PrimAlgorithm::prim(*graph, queue);
    cout << mst->getTotalWeight() << endl;
    mst->print();

    SinglyLinkedList<Edge> edgeList;
    graph->readToEdgeList(edgeList);
    QuickSort::quickSort(edgeList);

    Graph* mst2 = KruskalAlgorithm::kruskal(*graph, edgeList);
    cout << mst->getTotalWeight() << endl;
    mst2->print();
    delete graph;
}
