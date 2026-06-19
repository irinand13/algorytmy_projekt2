

#ifndef RUNNER_H
#define RUNNER_H
#include <iostream>
#include <ostream>
#include <chrono>
#include <climits>
#include <string>
#include <fstream>

#include "BellmanFordAlgorithm.h"
#include "DijkstraAlgorithm.h"
#include "FileReader.h"
#include "FileWriter.h"
#include "FordFulkersonAlgorithm.h"
#include "GenerateGraph.h"
#include "Graph.h"
#include "KruskalAlgorithm.h"
#include "Parameters.h"
#include "PrimAlgorithm.h"

class Runner {
public:
    void run() {
        if (Parameters::runMode == Parameters::RunModes::help) {
            Parameters::help();
            return;
        }
        if (Parameters::runMode == Parameters::RunModes::benchmark) {
            runBenchmark();
        } else if (Parameters::runMode == Parameters::RunModes::singleFile) {
            runSingleFile();
        }
    }

private:
    void clearEdgeList(SinglyLinkedList<Edge> &edgeList) {
        while (edgeList.getSize() > 0) {
            edgeList.popFront();
        }
    }

    void executeSingleKruskalBenchmark(std::ofstream &file, int iterations, Graph &graph, FileWriter &writer,
                                       bool useMatrix, SinglyLinkedList<Edge> &edgeList) {
        long long sum = 0;
        long long minTime = LLONG_MAX;
        long long maxTime = LLONG_MIN;

        std::string structName = useMatrix ? "Macierz Incydencji" : "Lista Nastepnikow";
        file << "# Algorytm: Kruskal | Badana struktura: " << structName << "\n";

        Parameters::problem = Parameters::Problems::mst;
        Parameters::algorithm = Parameters::Algorithms::kruskal;
        Parameters::structure = useMatrix
                                    ? Parameters::Structures::incidenceMatrix
                                    : Parameters::Structures::adjacencyList;

        for (int i = 0; i < iterations; i++) {
            clearEdgeList(edgeList);

            auto start = std::chrono::high_resolution_clock::now();

            if (useMatrix) graph.readMatrixToEdgeList(edgeList);
            else graph.readAdjacencyToEdgeList(edgeList);

            Graph *kgraph = KruskalAlgorithm::kruskal(graph.getVertexCount(), edgeList);

            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            sum += duration;
            delete kgraph;
            if (duration < minTime) minTime = duration;
            if (duration > maxTime) maxTime = duration;

            writer.writeSingleIteration(file, i + 1, duration);
        }
        writer.writeSummary(file, sum / iterations, minTime, maxTime);
    }

    void benchmarkKruskal(std::ofstream &file, int iterations, Graph &graph, FileWriter &writer) {
        SinglyLinkedList<Edge> edgeList;
        switch (Parameters::structure) {
            case Parameters::Structures::allStructures:
                executeSingleKruskalBenchmark(file, iterations, graph, writer, true, edgeList);
                executeSingleKruskalBenchmark(file, iterations, graph, writer, false, edgeList);
                Parameters::structure = Parameters::Structures::allStructures;
                break;
            case Parameters::Structures::incidenceMatrix:
                executeSingleKruskalBenchmark(file, iterations, graph, writer, true, edgeList);
                break;
            case Parameters::Structures::adjacencyList:
                executeSingleKruskalBenchmark(file, iterations, graph, writer, false, edgeList);
                break;
            default:
                std::cerr << "Error: unknown structure!" << std::endl;
        }
    }


    void executeSinglePrimBenchmark(std::ofstream &file, int iterations, Graph &graph, FileWriter &writer,
                                    bool useMatrix, SinglyLinkedList<Edge> &edgeList) {
        long long sum = 0;
        long long minTime = LLONG_MAX;
        long long maxTime = LLONG_MIN;

        std::string structName = useMatrix ? "Macierz Incydencji" : "Lista Nastepnikow";
        file << "# Algorytm: Prim | Badana struktura: " << structName << "\n";

        Parameters::problem = Parameters::Problems::mst;
        Parameters::algorithm = Parameters::Algorithms::prim;
        Parameters::structure = useMatrix
                                    ? Parameters::Structures::incidenceMatrix
                                    : Parameters::Structures::adjacencyList;

        for (int i = 0; i < iterations; i++) {
            clearEdgeList(edgeList);

            auto start = std::chrono::high_resolution_clock::now();

            if (useMatrix) graph.readMatrixToEdgeList(edgeList);
            else graph.readAdjacencyToEdgeList(edgeList);

            Graph *pgraph = PrimAlgorithm::prim(graph.getVertexCount(), edgeList);

            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            sum += duration;
            delete pgraph;
            if (duration < minTime) minTime = duration;
            if (duration > maxTime) maxTime = duration;

            writer.writeSingleIteration(file, i + 1, duration);
        }
        writer.writeSummary(file, sum / iterations, minTime, maxTime);
    }

    void benchmarkPrim(std::ofstream &file, int iterations, Graph &graph, FileWriter &writer) {
        SinglyLinkedList<Edge> edgeList;
        switch (Parameters::structure) {
            case Parameters::Structures::allStructures:
                executeSinglePrimBenchmark(file, iterations, graph, writer, true, edgeList);
                executeSinglePrimBenchmark(file, iterations, graph, writer, false, edgeList);
                Parameters::structure = Parameters::Structures::allStructures;
                break;
            case Parameters::Structures::incidenceMatrix:
                executeSinglePrimBenchmark(file, iterations, graph, writer, true, edgeList);
                break;
            case Parameters::Structures::adjacencyList:
                executeSinglePrimBenchmark(file, iterations, graph, writer, false, edgeList);
                break;
            default:
                std::cerr << "Error: unknown structure!"<< std::endl;
        }
    }


    void executeSingleDijkstraBenchmark(std::ofstream &file, int iterations, Graph &graph, FileWriter &writer,
                                        bool useMatrix) {
        long long sum = 0;
        long long minTime = LLONG_MAX;
        long long maxTime = LLONG_MIN;

        std::string structName = useMatrix ? "Macierz Incydencji" : "Lista Nastepnikow";
        file << "# Algorytm: Dijkstra | Badana struktura: " << structName << "\n";

        Parameters::problem = Parameters::Problems::sp;
        Parameters::algorithm = Parameters::Algorithms::dijkstra;
        Parameters::structure = useMatrix
                                    ? Parameters::Structures::incidenceMatrix
                                    : Parameters::Structures::adjacencyList;

        for (int i = 0; i < iterations; i++) {
            auto start = std::chrono::high_resolution_clock::now();

            Graph *dgraph = DijkstraAlgorithm::dijkstra(
                graph, Parameters::vertexStart, Parameters::vertexEnd, useMatrix);

            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            sum += duration;
            delete dgraph;
            if (duration < minTime) minTime = duration;
            if (duration > maxTime) maxTime = duration;

            writer.writeSingleIteration(file, i + 1, duration);
        }
        writer.writeSummary(file, sum / iterations, minTime, maxTime);
    }

    void benchmarkDijkstra(std::ofstream &file, int iterations, Graph &graph, FileWriter &writer) {
        switch (Parameters::structure) {
            case Parameters::Structures::allStructures:
                executeSingleDijkstraBenchmark(file, iterations, graph, writer, true);
                executeSingleDijkstraBenchmark(file, iterations, graph, writer, false);
                Parameters::structure = Parameters::Structures::allStructures;
                break;
            case Parameters::Structures::incidenceMatrix:
                executeSingleDijkstraBenchmark(file, iterations, graph, writer, true);
                break;
            case Parameters::Structures::adjacencyList:
                executeSingleDijkstraBenchmark(file, iterations, graph, writer, false);
                break;
            default:
                std::cerr << "Error: unknown structure!" << std::endl;
        }
    }


    void executeSingleBellmanFordBenchmark(std::ofstream &file, int iterations, Graph &graph, FileWriter &writer,
                                           bool useMatrix) {
        long long sum = 0;
        long long minTime = LLONG_MAX;
        long long maxTime = LLONG_MIN;

        std::string structName = useMatrix ? "Macierz Incydencji" : "Lista Nastepnikow";
        file << "# Algorytm: Bellman-Ford | Badana struktura: " << structName << "\n";

        Parameters::problem = Parameters::Problems::sp;
        Parameters::algorithm = Parameters::Algorithms::bellmanFord;
        Parameters::structure = useMatrix
                                    ? Parameters::Structures::incidenceMatrix
                                    : Parameters::Structures::adjacencyList;

        for (int i = 0; i < iterations; i++) {
            auto start = std::chrono::high_resolution_clock::now();

            Graph *bgraph = BellmanFordAlgorithm::bellmanFord(
                graph, Parameters::vertexStart, Parameters::vertexEnd, useMatrix);

            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            sum += duration;
            delete bgraph;
            if (duration < minTime) minTime = duration;
            if (duration > maxTime) maxTime = duration;

            writer.writeSingleIteration(file, i + 1, duration);
        }
        writer.writeSummary(file, sum / iterations, minTime, maxTime);
    }

    void benchmarkBellmanFord(std::ofstream &file, int iterations, Graph &graph, FileWriter &writer) {
        switch (Parameters::structure) {
            case Parameters::Structures::allStructures:
                executeSingleBellmanFordBenchmark(file, iterations, graph, writer, true);
                executeSingleBellmanFordBenchmark(file, iterations, graph, writer, false);
                Parameters::structure = Parameters::Structures::allStructures;
                break;
            case Parameters::Structures::incidenceMatrix:
                executeSingleBellmanFordBenchmark(file, iterations, graph, writer, true);
                break;
            case Parameters::Structures::adjacencyList:
                executeSingleBellmanFordBenchmark(file, iterations, graph, writer, false);
                break;
            default:
                std::cerr << "Error: unknown structure!" << std::endl;
        }
    }


    void executeSingleMfBenchmark(std::ofstream &file, int iterations, Graph &graph, FileWriter &writer,
                                  bool useMatrix) {
        long long sum = 0;
        long long minTime = LLONG_MAX;
        long long maxTime = LLONG_MIN;

        std::string structName = useMatrix ? "Macierz Incydencji" : "Lista Nastepnikow";
        file << "# Algorytm: Ford-Fulkerson | Badana struktura: " << structName << "\n";

        Parameters::problem = Parameters::Problems::mf;
        Parameters::algorithm = Parameters::Algorithms::fordFulkerson;
        Parameters::structure = useMatrix
                                    ? Parameters::Structures::incidenceMatrix
                                    : Parameters::Structures::adjacencyList;

        for (int i = 0; i < iterations; i++) {
            auto start = std::chrono::high_resolution_clock::now();

            int maxFlow = 0;
            Graph *fgraph = FordFulkersonAlgorithm::fordFulkerson(
                graph, Parameters::vertexStart, Parameters::vertexEnd, maxFlow, useMatrix);

            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            sum += duration;
            delete fgraph;
            if (duration < minTime) minTime = duration;
            if (duration > maxTime) maxTime = duration;

            writer.writeSingleIteration(file, i + 1, duration);
        }
        writer.writeSummary(file, sum / iterations, minTime, maxTime);
    }

    void runMfBenchmark(std::ofstream &file, int iterations, Graph &graph) {
        FileWriter writer;
        switch (Parameters::structure) {
            case Parameters::Structures::allStructures:
                executeSingleMfBenchmark(file, iterations, graph, writer, true);
                executeSingleMfBenchmark(file, iterations, graph, writer, false);
                Parameters::structure = Parameters::Structures::allStructures;
                break;
            case Parameters::Structures::incidenceMatrix:
                executeSingleMfBenchmark(file, iterations, graph, writer, true);
                break;
            case Parameters::Structures::adjacencyList:
                executeSingleMfBenchmark(file, iterations, graph, writer, false);
                break;
            default:
                std::cerr << "Error: unknown structure!" << std::endl;
        }
    }

    void runMstBenchmark(std::ofstream &file, int iterations, Graph &graph) {
        FileWriter writer;
        switch (Parameters::algorithm) {
            case Parameters::Algorithms::kruskal: benchmarkKruskal(file, iterations, graph, writer);
                break;
            case Parameters::Algorithms::prim: benchmarkPrim(file, iterations, graph, writer);
                break;
            case Parameters::Algorithms::allAlgorithms:
                benchmarkKruskal(file, iterations, graph, writer);
                benchmarkPrim(file, iterations, graph, writer);
                Parameters::algorithm = Parameters::Algorithms::allAlgorithms;
                break;
            default: std::cerr << "Error: Unsupported algorithm for MST!" << std::endl;
        }
    }

    void runSpBenchmark(std::ofstream &file, int iterations, Graph &graph) {
        FileWriter writer;
        switch (Parameters::algorithm) {
            case Parameters::Algorithms::dijkstra: benchmarkDijkstra(file, iterations, graph, writer);
                break;
            case Parameters::Algorithms::bellmanFord: benchmarkBellmanFord(file, iterations, graph, writer);
                break;
            case Parameters::Algorithms::allAlgorithms:
                benchmarkDijkstra(file, iterations, graph, writer);
                benchmarkBellmanFord(file, iterations, graph, writer);
                Parameters::algorithm = Parameters::Algorithms::allAlgorithms;
                break;
            default: std::cerr << "Error: Unsupported algorithm for Shortest Path!" << std::endl;
        }
    }

    void loadEdgesSingleFile(Graph &graph, SinglyLinkedList<Edge> &edgeList) {
        if (Parameters::structure == Parameters::Structures::incidenceMatrix) {
            graph.readMatrixToEdgeList(edgeList);
        } else {
            graph.readAdjacencyToEdgeList(edgeList);
        }
    }

    void runMstSingleFile(std::string &input, std::string &output) {
        FileReader reader;
        FileWriter writer;
        Graph *graph = reader.readToGraph(input, false);
        SinglyLinkedList<Edge> edgeList;

        loadEdgesSingleFile(*graph, edgeList);

        switch (Parameters::algorithm) {
            case Parameters::Algorithms::prim: {
                Graph *pGraph = PrimAlgorithm::prim(graph->getVertexCount(), edgeList);
                writer.writeFromGraph(output, graph, pGraph, pGraph->getTotalWeight());
                delete pGraph;
                break;
            }
            case Parameters::Algorithms::kruskal: {
                Graph *kGraph = KruskalAlgorithm::kruskal(graph->getVertexCount(), edgeList);
                writer.writeFromGraph(output, graph, kGraph, kGraph->getTotalWeight());
                delete kGraph;
                break;
            }
            default: std::cerr << "Error: Single file mode doesn't support 'allAlgorithms'!" << std::endl;
        }
        delete graph;
    }

    void runSpSingleFile(std::string &input, std::string &output) {
        FileWriter writer;
        FileReader reader;
        Graph *graph = reader.readToGraph(input, true);
        bool useMatrix = (Parameters::structure == Parameters::Structures::incidenceMatrix);

        switch (Parameters::algorithm) {
            case Parameters::Algorithms::dijkstra: {
                Graph *dGraph = DijkstraAlgorithm::dijkstra(
                    *graph, Parameters::vertexStart, Parameters::vertexEnd, useMatrix);
                writer.writeFromGraph(output, graph, dGraph, dGraph->getTotalWeight());
                delete dGraph;
                break;
            }
            case Parameters::Algorithms::bellmanFord: {
                Graph *bGraph = BellmanFordAlgorithm::bellmanFord(
                    *graph, Parameters::vertexStart, Parameters::vertexEnd, useMatrix);
                writer.writeFromGraph(output, graph, bGraph, bGraph->getTotalWeight());
                delete bGraph;
                break;
            }
            default: std::cerr << "Error: Single file mode doesn't support 'allAlgorithms'!" << std::endl;
        }
        delete graph;
    }

    void runSingleFile() {
        FileReader reader;
        FileWriter writer;
        std::cout << "Start runSingleFile" << std::endl;
        std::string inFile = Parameters::inputFile;
        std::string outFile = Parameters::outputFile;

        switch (Parameters::problem) {
            case Parameters::Problems::mf: {
                Graph *graph = reader.readToGraph(inFile, true);
                bool useMatrix = (Parameters::structure == Parameters::Structures::incidenceMatrix);

                int maxFlow = 0;
                Graph *fGraph = FordFulkersonAlgorithm::fordFulkerson(
                    *graph, Parameters::vertexStart, Parameters::vertexEnd, maxFlow, useMatrix);
                writer.writeFromGraph(outFile, graph, fGraph, maxFlow);
                delete fGraph;
                delete graph;
                break;
            }
            case Parameters::Problems::mst: runMstSingleFile(inFile, outFile);
                break;
            case Parameters::Problems::sp: runSpSingleFile(inFile, outFile);
                break;
            default: std::cerr << "Error: Unsupported problem type!" << std::endl;
        }
    }

    void runBenchmark() {
        FileWriter writer;
        writer.prepareFile(Parameters::resultsFile);
        std::ofstream file(Parameters::resultsFile, std::ios::app);

        if (!file.is_open()) {
            std::cerr << "Can't open file\n";
            return;
        }
        int vertexCount = Parameters::vertexCount;
        int iterations = Parameters::iterations;
        Graph *dgraph = GenerateGraph::generateGraph(vertexCount, true, Parameters::density);
        Graph *ndgraph = GenerateGraph::generateGraph(vertexCount, false, Parameters::density);

        switch (Parameters::problem) {
            case Parameters::Problems::mf: runMfBenchmark(file, iterations, *dgraph);
                break;
            case Parameters::Problems::mst: runMstBenchmark(file, iterations, *ndgraph);
                break;
            case Parameters::Problems::sp: runSpBenchmark(file, iterations, *dgraph);
                break;
            default: std::cerr << "Error: Unsupported problem type!" << std::endl;
        }
        delete dgraph;
        delete ndgraph;
        file.close();
    }
};
#endif //RUNNER_H
