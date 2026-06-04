//
// Created by iraan on 16.05.2026.
//

#ifndef GENERATEGRAPH_H
#define GENERATEGRAPH_H
#include "Graph.h"

namespace GenerateGraph {
    Graph* generateGraph(int n, bool directed, int density) {

        int edgeCount;
        int minEdges = n;
        int maxEdges = directed ? n*(n-1) : n*(n-1)/2;
        auto graph = new Graph(n, directed, maxEdges);
        srand(time(nullptr));

        // Sprawdza gęstość i ustawia liczbę krawędzi według tej gęstości
        switch (density) {
            case 25: edgeCount = (int)(maxEdges*0.25); break;
            case 50: edgeCount = (int)(maxEdges*0.50); break;
            case 75: edgeCount = (int)(maxEdges*0.75); break;
            case 99: edgeCount = (int)(maxEdges*0.99); break;
            default:
                edgeCount = (int)(maxEdges); break;
        }

        //Tablica wszystkich wierzchołków
        int verteces[n];
        for (int i = 0; i < n; i++) {
            verteces[i] = i; // wypełnienie wartościami
        }

        // Losowanie wartości w tablicy
        for (int i = n-1; i >= 0; i--) {
            int j = rand() % (i+1);
            //zamiana wartości
            int temp = verteces[i];
            verteces[i] = verteces[j];
            verteces[j] = temp;
        }

        //Ustawienie zakresu wag na podstawie ilości krawędzi
        int weightRange = edgeCount * 4 / 5;
        if (weightRange < 1) weightRange = 1;


        //Tworzenie drzewa spinającego
        int added = 0;
        for (int i = 0; i < n - 1; i++) {
            if (added == minEdges) break;

            int from = verteces[i];
            int to = verteces[i + 1];
            int weight = rand() % weightRange + 1;

            //Dodawanie krawędzi do grafu
            Vertex vu = graph->getVertex(from);
            Vertex vv = graph->getVertex(to);
            graph->addEdge(vu, vv, weight);
            added++;
        }

        int from = verteces[n-1];
        int to = verteces[0];
        int weight = rand() % weightRange + 1;

        Vertex vu = graph->getVertex(from);
        Vertex vv = graph->getVertex(to);
        graph->addEdge(vu, vv, weight);
        added++;


        //Tworzenie dodatkowych losowych krawędzi na podstawie ilości krawędzi, która została
        int newAdded = 0;
        int t = edgeCount - minEdges;
        for (int i = 0; i < t; i++) {
            if(newAdded == t) break;

            do {
                from = verteces[rand() % n];
                to = verteces[rand() % n];
            } while (from == to);

            int weight = rand() % weightRange + 1;

            //Dodawanie krawędzi do grafu
            Vertex u = graph->getVertex(from);
            Vertex v = graph->getVertex(to);
            graph->addEdge(u, v, weight);
            newAdded++;
        }
        return graph;
    }
}
#endif //GENERATEGRAPH_H
