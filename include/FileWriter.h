

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

        // lista sąsiedztwa
        file << "Adjacency list:\n";
        for (int i = 0; i < graph->getVertexCount(); i++) {
            file << i << ": ";
            SinglyLinkedList<Neighbor>::Node* current = graph->getAdjacencyList(i);
            while (current != nullptr) {
                file << "-> " << current->data.to.id
                     << " (w:" << current->data.weight << ") ";
                current = current->next;
            }
            file << "\n";
        }

        // macierz incydencji
        file << "\nIncidency matrix:\n";
        file << "    ";
        for (int i = 0; i < graph->getVertexCount(); i++)
            file << "v" << i << " ";
        file << "\n";

        for (int j = 0; j < graph->getEdgeCount(); j++) {
            file << "e" << j << ": ";
            for (int i = 0; i < graph->getVertexCount(); i++)
                file << " " << graph->getMatrixValue(i, j) << " ";
            file << "\n";
        }

        file.close();
    }
};
#endif //FILEWRITER_H

