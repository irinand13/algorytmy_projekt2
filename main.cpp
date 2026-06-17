#include <iostream>
#include <GenerateGraph.h>

#include "BellmanFordAlgorithm.h"
#include "DijkstraAlgorithm.h"
#include "FileReader.h"
#include "FileWriter.h"

#include "KruskalAlgorithm.h"
#include "PrimAlgorithm.h"
using namespace std;
int main() {
    FileWriter writer;
    string fileName = "dane.txt";

    srand(time(nullptr));
    Graph* graph = GenerateGraph::generateGraph(10,true,25);
    graph->print();
    if (graph->isConnected()) cout << "Connected" << endl;
    else cout << "Not Connected" << endl;
    writer.writeFromGraph("output.txt", graph);
    Graph* dgraph= DijkstraAlgorithm::dijkstraAlgorithm(*graph,0,9);
    Graph* bgraph= BellmanFordAlgorithm::BellmanFord(*graph,0,9);

    cout << dgraph->getTotalWeight() << endl;
    dgraph->print();
    cout << bgraph->getTotalWeight() << endl;
    bgraph->print();

    delete graph;
    delete dgraph;
    delete bgraph;
    // writer.writeFromGraph("output.txt", graph);
    //
    // graph->print();
    // Graph* mst = PrimAlgorithm::prim(*graph);
    // cout << mst->getTotalWeight() << endl;
    // mst->print();
    //
    //
    //
    // Graph* mst2 = KruskalAlgorithm::kruskal(*graph);
    // cout << mst->getTotalWeight() << endl;
    // mst2->print();

    // delete mst;
    // delete mst2;

//     try {
//         Graph* g = reader.readToGraph("dane.txt", false);
//
//         // Sprawdź czy graf ma odpowiednią liczbę wierzchołków/krawędzi
//         std::cout << "Graf wczytany pomyślnie!" << std::endl;
//
//         // Jeśli Graph ma metodę print() lub podobną – wywołaj ją
//         g->print();
//
//         delete g;
//     } catch (const std::runtime_error& e) {
//         std::cerr << "Błąd: " << e.what() << std::endl;
//     }
//
//     return 0;
}


