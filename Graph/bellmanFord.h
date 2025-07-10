#pragma once
#include "Graph.h"

/*
Single Source Shortest Path Algorithm.
Works for every graph even with negative weight edges.

Time Complexity: O(V * E)
Space Complexity: O(V)
*/

/*
Algorithm

1. Set all distances to infinity except the source vertex which is set to 0.
2. Iterate through all edges |V| - 1 times.
2(a) If a node is unreachable (INFINITY), skip it.
2(b) For each reachable node, relax all its edges.
3. Iterate through all edges again to check for negative weight cycles.
3(a) If a node is reachable and its distance can be relaxed, set it to INT_MIN (Cuz it is a negative cycle).

*/

template <typename T>
void Graph<T>::bellmanFord(T s)
{
    std::unordered_map<T, int> dist;
    std::unordered_map<T, T> parent;
    for (auto [k, v] : adjList)
    {
        dist[k] = INT_MAX;
    }
    dist[s] = 0;

    for (int i = 0; i < vertices - 1; i++)
    {
        bool anyChange = false;
        for (auto [k, v] : adjList)
        {
            if (dist[k] == INT_MAX)
            {
                continue;
            }
            for (std::pair<T, int> p : v)
            {
                int newDist = dist[k] + p.second;
                if (newDist < dist[p.first])
                {
                    dist[p.first] = newDist;
                    parent[p.first] = k;
                    anyChange = true;
                }
            }
        }
        if (!anyChange)
        {
            break;
        }
    }

    bool negCycle = false;
    T cycleNode;
    for (auto [k, v] : adjList)
    {
        if (dist[k] == INT_MAX)
        {
            continue;
        }
        for (std::pair<T, int> p : v)
        {
            int newDist = dist[k] + p.second;

            if (newDist < dist[p.first])
            {
                dist[p.first] = INT_MIN;
                parent[p.first] = k;
                negCycle = true;
                cycleNode = p.first;
            }
        }
    }

    if (negCycle)
    {
        std::cout << "Negative Cycle\n";
        for (T u : constructPath(parent[cycleNode], cycleNode, parent))
        {
            std::cout << u << ' ';
            dist[u] = INT_MIN;
        }
        std::cout << '\n';
    }

    std::cout << "Shortest Distance\n";
    for (auto [k, v] : adjList)
    {
        std::cout << k << ": " << dist[k] << '\n';
    }
}
