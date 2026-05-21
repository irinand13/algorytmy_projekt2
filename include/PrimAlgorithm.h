//
// Created by iraan on 02.05.2026.
//

#ifndef PRIMALGORITHM_H
#define PRIMALGORITHM_H
#include "Graph.h"
using namespace std;

namespace PrimAlgorithm {

    template<class T>
    void prim(Graph& graph, int start) {
        int vertexCount = graph.getVertexCount();
        for (int i = 0; i < vertexCount; i++) {
            graph.getVertex(i).colored = false;
        }
    }

};
#endif //PRIMALGORITHM_H
