#pragma once

// #include "Graph.h"
#include <set>
/*
Works for only Graph with no negative weight edges.

-> Single Source Shortest Path

1. For Dense Graphs (m ≈ n^2):
T.C = O(n^2 + m)

2. For Sparse Graphs (m ≈ n):
T.C = O( (n + m) log n)

*/

template <typename T>
void Graph<T>::dijkstra(T s, bool denseGraph)
{
    if (!weighted)
    {
        std::cout << "Dijkstra is not applicable on unweighted graph.\n";
        return;
    }

    std::unordered_map<T, int> dist;
    std::unordered_map<T, T> parent;
    for (auto [k, v] : adjList)
    {
        dist[k] = INT_MAX;
    }
    dist[s] = 0;

    if (denseGraph)
    {
        std::unordered_set<T> visited;
        for (int i = 0; i < vertices; i++)
        {
            T u;
            for (auto [v, V] : adjList)
            {
                // Selecting node with smallest distance
                if ((visited.find(v) == visited.end()) && (adjList.find(u) == adjList.end() || dist[v] < dist[u]))
                {
                    u = v;
                }
            }

            if (dist[u] == INT_MAX)
            {
                break;
            }
            visited.insert(u);

            // Relaxing Edges
            for (auto [v, w] : adjList[u])
            {
                if ((dist[u] + w) < dist[v])
                {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                }
            }
        }
    }
    else
    {
        std::set<std::pair<int, T>> q;
        q.insert({0, s});
        T u;
        int d;
        while (!q.empty())
        {
            u = q.begin()->second;
            d = q.begin()->first;
            q.erase(q.begin());

            for (auto [v, w] : adjList[u])
            {
                if ((d + w) < dist[v])
                {
                    q.erase({dist[v], v});
                    dist[v] = d + w;
                    q.insert({dist[v], v});
                    parent[v] = u;
                }
            }
        }
    }

    std::cout << "Shortest Distance\n";
    for (auto [k, v] : dist)
    {
        std::cout << k << ": " << v << '\n';
    }

    std::cout << "Shortest Path\n";
    for (auto [k, v] : dist)
    {
        for (T u : constructPath(k, s, parent))
        {
            std::cout << u << ' ';
        }
        std::cout << '\n';
    }
}
