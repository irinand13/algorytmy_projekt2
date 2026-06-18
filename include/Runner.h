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
        } else if (Parameters::runMode == Parameters::RunModes::help) {
            Parameters::help();
        }
    }

private:
    void benchmarkKruskal(std::ofstream& file, int iterations, Graph& graph, FileWriter& writer) {
        long long sum = 0;
        long long minTime = LLONG_MAX;
        long long maxTime = LLONG_MIN;

        for (int i = 0; i < iterations; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            Graph* kgraph = KruskalAlgorithm::kruskal(graph);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            sum += duration;
            delete kgraph;
            if (duration < minTime) minTime = duration;
            if (duration > maxTime) maxTime = duration;
            writer.writeSingleIteration(file, iterations, duration);
        }
        long long averagek = sum / iterations;
        writer.writeSummary(file, averagek, minTime, maxTime);
    }

    void benchmarkPrim(std::ofstream& file, int iterations, Graph& graph, FileWriter& writer) {
        long long sum = 0;
        long long minTime = LLONG_MAX;
        long long maxTime = LLONG_MIN;

        for (int i = 0; i < iterations; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            Graph* pgraph = PrimAlgorithm::prim(graph);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            sum += duration;
            delete pgraph;
            if (duration < minTime) minTime = duration;
            if (duration > maxTime) maxTime = duration;
            writer.writeSingleIteration(file, iterations, duration);
        }
        long long averagep = sum / iterations;
        writer.writeSummary(file, averagep, minTime, maxTime);
    }

    void runMstBenchmark(std::ofstream& file, int iterations, Graph& graph) {
        FileWriter writer;

        switch (Parameters::algorithm) {
            case Parameters::Algorithms::kruskal:
                benchmarkKruskal(file, iterations, graph, writer);
                break;
            case Parameters::Algorithms::prim:
                benchmarkPrim(file, iterations, graph, writer);
                break;
            case Parameters::Algorithms::allAlgorithms:
                std::cout << "Running all MST algorithms..." << std::endl;
                Parameters::algorithm = Parameters::Algorithms::kruskal;
                benchmarkKruskal(file, iterations, graph, writer);
                
                Parameters::algorithm = Parameters::Algorithms::prim;
                benchmarkPrim(file, iterations, graph, writer);
                
                Parameters::algorithm = Parameters::Algorithms::allAlgorithms;
                break;
            default:
                std::cerr << "Error: Unsupported algorithm for MST!" << std::endl;
        }
    }

    void benchmarkDijkstra(std::ofstream& file, int iterations, Graph& graph, FileWriter& writer) {
        long long sum = 0;
        long long minTime = LLONG_MAX;
        long long maxTime = LLONG_MIN;

        for (int i = 0; i < iterations; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            Graph* dgraph = DijkstraAlgorithm::dijkstraAlgorithm(graph, Parameters::vertexStart, Parameters::vertexEnd);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            sum += duration;
            delete dgraph;
            if (duration < minTime) minTime = duration;
            if (duration > maxTime) maxTime = duration;
            writer.writeSingleIteration(file, iterations, duration);
        }
        long long averaged = sum / iterations;
        writer.writeSummary(file, averaged, minTime, maxTime);
    }

    void benchmarkBellmanFord(std::ofstream& file, int iterations, Graph& graph, FileWriter& writer) {
        long long sum = 0;
        long long minTime = LLONG_MAX;
        long long maxTime = LLONG_MIN;

        for (int i = 0; i < iterations; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            Graph* bgraph = BellmanFordAlgorithm::BellmanFord(graph, Parameters::vertexStart, Parameters::vertexEnd);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            sum += duration;
            delete bgraph;
            if (duration < minTime) minTime = duration;
            if (duration > maxTime) maxTime = duration;
            writer.writeSingleIteration(file, iterations, duration);
        }
        long long averageb = sum / iterations;
        writer.writeSummary(file, averageb, minTime, maxTime);
    }

    void runSpBenchmark(std::ofstream& file, int iterations, Graph& graph) {
        FileWriter writer;

        switch (Parameters::algorithm) {
            case Parameters::Algorithms::dijkstra:
                benchmarkDijkstra(file, iterations, graph, writer);
                break;
            case Parameters::Algorithms::bellmanFord:
                benchmarkBellmanFord(file, iterations, graph, writer);
                break;
            case Parameters::Algorithms::allAlgorithms:
                std::cout << "Running all Shortest Path algorithms..." << std::endl;
                Parameters::algorithm = Parameters::Algorithms::dijkstra;
                benchmarkDijkstra(file, iterations, graph, writer);
                
                Parameters::algorithm = Parameters::Algorithms::bellmanFord;
                benchmarkBellmanFord(file, iterations, graph, writer);
                
                Parameters::algorithm = Parameters::Algorithms::allAlgorithms;
                break;
            default:
                std::cerr << "Error: Unsupported algorithm for Shortest Path!" << std::endl;
        }
    }

    void runMfBenchmark(std::ofstream& file, int iterations, Graph& graph) {
        FileWriter writer;
        long long sum = 0;
        long long minTime = LLONG_MAX;
        long long maxTime = LLONG_MIN;

        for (int i = 0; i < iterations; i++) {
            int maxFlow = 0;
            auto start = std::chrono::high_resolution_clock::now();
            Graph* dgraph = FordFulkersonAlgorithm::fordFulkerson(graph, Parameters::vertexStart, Parameters::vertexEnd, maxFlow);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            sum += duration;
            delete dgraph;
            if (duration < minTime) minTime = duration;
            if (duration > maxTime) maxTime = duration;
            writer.writeSingleIteration(file, iterations, duration);
        }
        long long average = sum / iterations;
        writer.writeSummary(file, average, minTime, maxTime);
    }

    void runMstSingleFile(std::string& input, std::string& output) {
        FileReader reader;
        FileWriter writer;
        Graph* graph = reader.readToGraph(input, false);
        int mst;
        switch (Parameters::algorithm) {
            case Parameters::Algorithms::prim: {
                Graph* pGraph = PrimAlgorithm::prim(*graph);
                mst = pGraph->getTotalWeight();
                writer.writeFromGraph(output, graph, pGraph, mst);
                delete pGraph;
                break;
            }
            case Parameters::Algorithms::kruskal: {
                Graph* kGraph = KruskalAlgorithm::kruskal(*graph);
                mst = kGraph->getTotalWeight();
                writer.writeFromGraph(output, graph, kGraph, mst);
                delete kGraph;
                break;
            }
            default:
                std::cerr << "Error: Single file mode doesn't support 'allAlgorithms'!" << std::endl;
        }
        delete graph;
    }

    void runSpSingleFile(std::string& input, std::string& output) {
        FileWriter writer;
        FileReader reader;
        Graph* graph = reader.readToGraph(input, true);
        int sp;
        switch (Parameters::algorithm) {
            case Parameters::Algorithms::dijkstra: {
                Graph* dGraph = DijkstraAlgorithm::dijkstraAlgorithm(*graph, Parameters::vertexStart, Parameters::vertexEnd);
                sp = dGraph->getTotalWeight();
                writer.writeFromGraph(output, graph, dGraph, sp);
                delete dGraph;
                break;
            }
            case Parameters::Algorithms::bellmanFord: {
                Graph* bGraph = BellmanFordAlgorithm::BellmanFord(*graph, Parameters::vertexStart, Parameters::vertexEnd);
                sp = bGraph->getTotalWeight();
                writer.writeFromGraph(output, graph, bGraph, sp);
                delete bGraph;
                break;
            }
            default:
                std::cerr << "Error: Single file mode doesn't support 'allAlgorithms'!" << std::endl;
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
                Graph* graph = reader.readToGraph(inFile, true);
                int maxFlow = 0;
                Graph* fGraph = FordFulkersonAlgorithm::fordFulkerson(
                    *graph, Parameters::vertexStart, Parameters::vertexEnd, maxFlow);
                writer.writeFromGraph(outFile, graph, fGraph, maxFlow);
                delete fGraph;
                delete graph;
                break;
            }
            case Parameters::Problems::mst: runMstSingleFile(inFile, outFile); break;
            case Parameters::Problems::sp: runSpSingleFile(inFile, outFile); break;
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
        Graph* dgraph = GenerateGraph::generateGraph(vertexCount, true, Parameters::density);
        Graph* ndgraph = GenerateGraph::generateGraph(vertexCount, false, Parameters::density);

        switch (Parameters::problem) {
            case Parameters::Problems::mf: runMfBenchmark(file, iterations, *dgraph); break;
            case Parameters::Problems::mst: runMstBenchmark(file, iterations, *ndgraph); break;
            case Parameters::Problems::sp: runSpBenchmark(file, iterations, *dgraph); break;
            default: std::cerr << "Error: Unsupported problem type!" << std::endl;
        }
        delete dgraph;
        delete ndgraph;
        file.close();
    }
};
#endif //RUNNER_H