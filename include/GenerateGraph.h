//
// Created by iraan on 16.05.2026.
//

#ifndef GENERATEGRAPH_H
#define GENERATEGRAPH_H
#include "Graph.h"

namespace GenerateGraph {
    Graph* generateGraph(int n, bool directed, int density) {

        int edgeCount;
        int minEdges = directed ? 2*(n-1) : n-1;
        int maxEdges = directed ? n*(n-1) : n*(n-1)/2;
        auto graph = new Graph(n, directed, maxEdges);
        srand(time(nullptr));

        switch (density) {
            case 25: edgeCount = (int)(maxEdges*0.25); break;
            case 50: edgeCount = (int)(maxEdges*0.50); break;
            case 75: edgeCount = (int)(maxEdges*0.75); break;
            case 99: edgeCount = (int)(maxEdges*99); break;
            default:
                edgeCount = (int)(maxEdges); break;
        }

        int verteces[n];
        for (int i = 0; i < n; i++) {
            verteces[i] = i;
        }

        for (int i = n-1; i >= 0; i--) {
            int j = rand() % i+1;
            int temp = verteces[i];
            verteces[i] = verteces[j];
            verteces[j] = temp;
        }

        int weightRange = edgeCount * 4 / 5;
        if (weightRange < 1) weightRange = 1;

        int added = 0;
        for (int i = 0; i < n; i++) {
            if (added == minEdges) break;

            int from = verteces[i];
            int to = verteces[rand() % i];
            int weight = rand() % weightRange + 1;

            Vertex vu = graph->getVertex(from);
            Vertex vv = graph->getVertex(to);
            graph->addEdge(vu, vv, weight);
            added++;
        }



        int newAdded = 0;
        int t = edgeCount - minEdges;
        for (int i = 0; i < t; i++) {
            if(newAdded == t) break;
            int from = verteces[rand() % n];
            int to = verteces[rand() % n];
            int weight = rand() % weightRange + 1;

            Vertex vu = graph->getVertex(from);
            Vertex vv = graph->getVertex(to);
            graph->addEdge(vu, vv, weight);
            newAdded++;
        }
        return graph;
    }
}
#endif //GENERATEGRAPH_H
