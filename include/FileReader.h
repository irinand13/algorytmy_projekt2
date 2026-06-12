//
// Created by iraan on 04.06.2026.
//

#ifndef FILEREADER_H
#define FILEREADER_H
#include "Graph.h"
#include <fstream>
#include <string>

class FileReader {

    //Odczytuje dane z pliku i tworzy graf
    public:
    Graph* readToGraph(const string& fileName, bool directed) {
        ifstream file(fileName);

        if(!file.is_open()) {
            cerr << "Error opening file " << fileName << endl;
            throw std::runtime_error("Cannot open file: " + fileName);
        }
        int vertexCount, edgeCount;
        file >> vertexCount >> edgeCount;

        auto* graph = new Graph(vertexCount, directed, edgeCount);

        for (int i = 0; i < edgeCount; i++) {
            int u, v, w;
            file >> u >> v >> w;

            Vertex& from = graph->getVertex(u);
            Vertex& to = graph->getVertex(v);
            graph->addEdge(from, to, w);
        }

    return graph;
    }
};
#endif //FILEREADER_H
