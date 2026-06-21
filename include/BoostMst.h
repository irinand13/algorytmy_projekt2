#ifndef BOOSTMST_H
#define BOOSTMST_H

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>
#include "Graph.h"

class BoostMST {
public:
    using BoostGraph = boost::adjacency_list<
        boost::vecS, boost::vecS, boost::undirectedS,
        boost::no_property,
        boost::property<boost::edge_weight_t, int>>;

    //wykonanie algorytmu na liście sąsiedztwa
    static BoostGraph fromAdjacency(Graph& graph) {
        BoostGraph g(graph.getVertexCount());
        auto weightMap = boost::get(boost::edge_weight, g);

        for (int i = 0; i < graph.getVertexCount(); i++) {
            auto* cur = graph.getAdjacencyList(i);
            while (cur != nullptr) {
                int j = cur->data.to.id;
                if (i < j) {
                    auto [e, ok] = boost::add_edge(i, j, g);
                    weightMap[e] = cur->data.weight;
                }
                cur = cur->next;
            }
        }
        return g;
    }

    //wykonanie algorytmu na macierzy incydencji
    static BoostGraph fromMatrix(Graph& graph) {
        BoostGraph g(graph.getVertexCount());
        auto weightMap = boost::get(boost::edge_weight, g);

        for (int col = 0; col < graph.getEdgeCount(); col++) {
            int from = -1, to = -1, weight = 0;
            for (int row = 0; row < graph.getVertexCount(); row++) {
                int val = graph.getMatrixValue(row, col);
                if (val > 0) {
                    if (from == -1) { from = row; weight = val; }
                    else            { to = row; }
                }
            }
            if (from != -1 && to != -1) {
                auto [e, ok] = boost::add_edge(from, to, g);
                weightMap[e] = weight;
            }
        }
        return g;
    }

    // algorytm Kruskala
    static void kruskal(BoostGraph& g) {
        using ED = boost::graph_traits<BoostGraph>::edge_descriptor;
        std::vector<ED> mst;
        boost::kruskal_minimum_spanning_tree(g, std::back_inserter(mst));
    }

    // algorytm Prima
    static void prim(BoostGraph& g) {
        int n = boost::num_vertices(g);
        using VD = boost::graph_traits<BoostGraph>::vertex_descriptor;
        std::vector<VD> pred(n);
        boost::prim_minimum_spanning_tree(g, pred.data());
    }
};

#endif
