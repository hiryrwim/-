#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <vector>
#include <queue>
#include <limits>
#include <utility>

struct Edge {
    int to;
    long long weight;
};

class Graph {
public:
    int vertices;
    std::vector<std::vector<Edge>> adj;

    Graph(int v);
    void addEdge(int from, int to, long long weight);
    std::vector<long long> shortestPath(int start);
};

#endif