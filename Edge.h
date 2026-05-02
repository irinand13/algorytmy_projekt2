//
// Created by iraan on 02.05.2026.
//

#ifndef EDGE_H
#define EDGE_H
struct Edge {
    int to;
    int weight;

public:
    Edge(int to, int weight) {
        this->to = to;
        this->weight = weight;
    }
};
#endif //EDGE_H
