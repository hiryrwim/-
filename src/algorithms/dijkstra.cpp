#include "dijkstra.h"

Graph::Graph(int v) : vertices(v), adj(v) {}

void Graph::addEdge(int from, int to, long long weight) {
    adj[from].push_back({to, weight});
}

std::vector<long long> Graph::shortestPath(int start) {
    std::vector<long long> dist(vertices, std::numeric_limits<long long>::max());
    dist[start] = 0;

    using P = std::pair<long long, int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [cost, u] = pq.top(); pq.pop();
        if (cost > dist[u]) continue;

        for (const auto& e : adj[u]) {
            long long newCost = cost + e.weight;
            if (newCost < dist[e.to]) {
                dist[e.to] = newCost;
                pq.push({newCost, e.to});
            }
        }
    }
    return dist;
}