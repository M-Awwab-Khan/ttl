#pragma once

#include "Graph.h"

/*
Works for only Graph with no negative weight edges.

Time Complexity: O(E * log V)
Space Complexity: O(V)
*/
template <typename T>
void Graph<T>::dijkstra(T s)
{
    if (!weighted)
    {
        std::cout << "Dijkstra not applicable on unweighted graph.\n";
        return;
    }

    std::unordered_map<T, int> dist;
    for (auto [k, v] : adjList)
    {
        dist[k] = INT_MAX;
    }

    std::priority_queue<std::pair<T, int>, std::vector<std::pair<T, int>>, Compare<T>> pq;
    dist[s] = 0;
    pq.push(std::make_pair(s, 0));

    T u, v;
    int w, d;
    while (!pq.empty())
    {
        u = pq.top().first;
        d = pq.top().second;
        pq.pop();

        for (std::pair<T, int> p : adjList[u])
        {
            v = p.first;
            w = p.second;
            if (dist[v] > d + w)
            {
                dist[v] = d + w;
                pq.push(std::make_pair(v, dist[v]));
            }
        }
    }

    std::cout << "Shortest Distance\n";
    for (auto [k, v] : dist)
    {
        std::cout << k << ": " << v << '\n';
    }
}
