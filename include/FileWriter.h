

#ifndef FILEWRITER_H
#define FILEWRITER_H
//
// Created by iraan on 04.06.2026.
//

#include <chrono>
#include "Graph.h"
#include <fstream>
#include <iomanip>
#include <string>
#include <ctime>
#include <stdexcept>

#include "Parameters.h"

class FileWriter {
public:
     void writeGraph(std::ofstream& file, Graph* graph) {
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
    }

    void writeFromGraph(const std::string& fileName, Graph* graph, Graph* result, int value) {
        std::ofstream file(fileName);
        if (!file.is_open()) throw std::runtime_error("Cannot open file: " + fileName);

        writeGraph(file, graph);
        file << "\n=== Result ===\n";
        writeGraph(file, result);
        file << "\nResult: " << value << "\n";

        file.close();
    }

    inline std::string getAlgorithmName(Parameters::Algorithms alg) {
        switch (alg) {
            case Parameters::Algorithms::prim: return "Prim";
            case Parameters::Algorithms::kruskal: return "Kruskal";
            case Parameters::Algorithms::dijkstra: return "Dijkstra";
            case Parameters::Algorithms::bellmanFord: return "BellmanFord";
            case Parameters::Algorithms::fordFulkerson: return "FordFulkerson";
            case Parameters::Algorithms::allAlgorithms: return "All";
            default: return "Unknown";
            }
        }

    inline std::string getProblemName(Parameters::Problems problem) {
        switch (problem) {
            case Parameters::Problems::mst: return "MST";
            case Parameters::Problems::sp: return "SP";
            case Parameters::Problems::mf: return "MF";
            default: return "Unknown";
        }
    }
    inline std::string getStructureName(Parameters::Structures str) {
        switch (str) {
            case Parameters::Structures::incidenceMatrix: return "IncidenceMatrix";
            case Parameters::Structures::adjacencyList: return "AdjacencyList";
            case Parameters::Structures::allStructures: return "All";
            default: return "Unknown";
        }
    }

    inline void prepareFile(const std::string& filename) {
        std::ifstream check(filename);
        bool isEmpty = !check.good() || check.peek() == std::ifstream::traits_type::eof();
        check.close();

        if (isEmpty) {
            std::ofstream file(filename, std::ios::out);
            if (file.is_open()) {
                file << "timestamp;problem;algorithm;structure;vertices;density;iterations;duration_us\n";
                file.close();
            }
        }
    }

    inline void writeSingleIteration(std::ofstream& file, int iterations, long long duration) {
        auto now = std::chrono::system_clock::now();
        std::time_t nowTime = std::chrono::system_clock::to_time_t(now);

        std::tm* timePtr = std::localtime(&nowTime);

        file << std::put_time(timePtr, "%Y-%m-%d %H:%M:%S") << ";"
             << getProblemName(Parameters::problem) << ";"
             << getAlgorithmName(Parameters::algorithm) << ";"
             << getStructureName(Parameters::structure) << ";"
             << Parameters::vertexCount << ";"
             << Parameters::density << ";"
             << iterations << ";"
             << duration << "\n"; // POPRAWKA: Usunięto tekst "SINGLE;" powodujący rozjechanie kolumn CSV
    }

    inline void writeSummary(std::ofstream& file, long long avg, long long min, long long max) {
        file << ";;;;;;;AVG: " << avg << "\n";
        file << ";;;;;;;MIN: " << min << "\n";
        file << ";;;;;;;MAX: " << max << "\n";
    }
};

#endif //FILEWRITER_H