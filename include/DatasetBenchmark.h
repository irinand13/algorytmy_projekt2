//
// Created by iraan on 19.06.2026.
//

#ifndef DATASETBENCHMARK_H
#define DATASETBENCHMARK_H

#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <climits>
#include "Graph.h"
#include "FileReader.h"
#include "KruskalAlgorithm.h"
#include "PrimAlgorithm.h"
#include "SinglyLinkedList.h"
#include "BoostMst.h"

class DatasetBenchmark {
public:
    static void runMst(const std::string& inputFile,
                       const std::string& outputFile,
                       int iterations = 10) {
        FileReader reader;
        Graph* graph = reader.readToGraph(inputFile, false);
        if (!graph) {
            std::cerr << "Nie udalo sie wczytac grafu z: " << inputFile << std::endl;
            return;
        }

        std::ofstream file(outputFile);
        if (!file.is_open()) {
            std::cerr << "Nie mozna otworzyc pliku: " << outputFile << std::endl;
            delete graph;
            return;
        }

        file << "algorytm,struktura,iteracja,czas_us\n";

        benchmarkKruskal(file, *graph, iterations, true);
        benchmarkKruskal(file, *graph, iterations, false);
        benchmarkPrim(file, *graph, iterations, true);
        benchmarkPrim(file, *graph, iterations, false);

        benchmarkBoostKruskal(file, *graph, iterations, true);
        benchmarkBoostKruskal(file, *graph, iterations, false);
        benchmarkBoostPrim(file, *graph, iterations, true);
        benchmarkBoostPrim(file, *graph, iterations, false);

        file.close();
        delete graph;
        std::cout << "Gotowe. Wyniki w: " << outputFile << std::endl;
    }

private:
    static void writeSummary(std::ofstream& file, const std::string& alg,
                             const std::string& struc, long long avg,
                             long long minT, long long maxT) {
        std::cout << alg << " [" << struc << "]"
                  << "  AVG: " << avg << " us"
                  << "  MIN: " << minT << " us"
                  << "  MAX: " << maxT << " us" << std::endl;
    }

    static void benchmarkKruskal(std::ofstream& file, Graph& graph,
                                  int iterations, bool useMatrix) {
        std::string struc = useMatrix ? "MacierzIncydencji" : "ListaSasiedztwa";
        long long sum = 0, minT = LLONG_MAX, maxT = LLONG_MIN;

        for (int i = 0; i < iterations; i++) {
            SinglyLinkedList<Edge> edgeList;
            auto start = std::chrono::high_resolution_clock::now();

            if (useMatrix) graph.readMatrixToEdgeList(edgeList);
            else graph.readAdjacencyToEdgeList(edgeList);
            Graph* result = KruskalAlgorithm::kruskal(graph.getVertexCount(), edgeList);

            auto end = std::chrono::high_resolution_clock::now();
            long long dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            file << "Kruskal," << struc << "," << (i + 1) << "," << dur << "\n";
            sum += dur;
            if (dur < minT) minT = dur;
            if (dur > maxT) maxT = dur;
            delete result;
        }
        writeSummary(file, "Kruskal", struc, sum / iterations, minT, maxT);
    }

    static void benchmarkPrim(std::ofstream& file, Graph& graph,
                               int iterations, bool useMatrix) {
        std::string struc = useMatrix ? "MacierzIncydencji" : "ListaSasiedztwa";
        long long sum = 0, minT = LLONG_MAX, maxT = LLONG_MIN;

        for (int i = 0; i < iterations; i++) {
            SinglyLinkedList<Edge> edgeList;
            auto start = std::chrono::high_resolution_clock::now();

            if (useMatrix) graph.readMatrixToEdgeList(edgeList);
            else graph.readAdjacencyToEdgeList(edgeList);
            Graph* result = PrimAlgorithm::prim(graph.getVertexCount(), edgeList);

            auto end = std::chrono::high_resolution_clock::now();
            long long dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            file << "Prim," << struc << "," << (i + 1) << "," << dur << "\n";
            sum += dur;
            if (dur < minT) minT = dur;
            if (dur > maxT) maxT = dur;
            delete result;
        }
        writeSummary(file, "Prim", struc, sum / iterations, minT, maxT);
    }

    static void benchmarkBoostKruskal(std::ofstream& file, Graph& graph,
                                       int iterations, bool useMatrix) {
        std::string struc = useMatrix ? "MacierzIncydencji" : "ListaSasiedztwa";
        long long sum = 0, minT = LLONG_MAX, maxT = LLONG_MIN;

        BoostMST::BoostGraph bg = useMatrix
            ? BoostMST::fromMatrix(graph)
            : BoostMST::fromAdjacency(graph);

        for (int i = 0; i < iterations; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            BoostMST::kruskal(bg);
            auto end = std::chrono::high_resolution_clock::now();

            long long dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            file << "BoostKruskal," << struc << "," << (i+1) << "," << dur << "\n";
            sum += dur; if (dur < minT) minT = dur; if (dur > maxT) maxT = dur;
        }
        writeSummary(file, "BoostKruskal", struc, sum / iterations, minT, maxT);
    }

    static void benchmarkBoostPrim(std::ofstream& file, Graph& graph,
                                    int iterations, bool useMatrix) {
        std::string struc = useMatrix ? "MacierzIncydencji" : "ListaSasiedztwa";
        long long sum = 0, minT = LLONG_MAX, maxT = LLONG_MIN;

        BoostMST::BoostGraph bg = useMatrix
            ? BoostMST::fromMatrix(graph)
            : BoostMST::fromAdjacency(graph);

        for (int i = 0; i < iterations; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            BoostMST::prim(bg);
            auto end = std::chrono::high_resolution_clock::now();

            long long dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            file << "BoostPrim," << struc << "," << (i+1) << "," << dur << "\n";
            sum += dur; if (dur < minT) minT = dur; if (dur > maxT) maxT = dur;
        }
        writeSummary(file, "BoostPrim", struc, sum / iterations, minT, maxT);
    }
};

#endif //DATASETBENCHMARK_H