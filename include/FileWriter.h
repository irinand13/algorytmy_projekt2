

#ifndef FILEWRITER_H
#define FILEWRITER_H
//
// Created by iraan on 04.06.2026.
//

#include "Graph.h"
#include <fstream>
#include <string>

class FileWriter {

    //Zapisuje graf do pliku
public:
    void writeFromGraph(const string& fileName, Graph* graph) {
        std::ofstream file(fileName);

        if (!file.is_open()) {
            std::cerr << "Error opening file " << fileName << endl;
            throw std::runtime_error("Cannot open file: " + fileName);
        }

        file << graph->getVertexCount() << "   " << graph->getEdgeCount() << "\n";

        for (int i = 0; i < graph->getVertexCount(); i++) {
            SinglyLinkedList<Neighbor>::Node* current = graph->getAdjacencyList(i);
            while (current != nullptr) {
                //jeżeli graf jest nieskierowany unika
                if (!graph->isDirected() && i > current->data.to.id) {
                    current = current->next;
                    continue;
                }
                file << i << "   " << current->data.to.id << "   " << current->data.weight << "\n";
                current = current->next;
            }
        }
        file.close();
    }
};
#endif //FILEWRITER_H

