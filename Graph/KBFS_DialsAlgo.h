#pragma once

#include "Graph.h"

/*
Single Source Shortest Path

When max weight is small number then
this algorihtm is better than bellman ford and dijkstra.

*/

template <typename T>
void Graph<T>::kBFS_DialsAlgo(T s, int maxWeight)
{
    std::vector<std::unordered_set<T>> buckets((vertices - 1) * maxWeight);
    std::unordered_map<T, int> dist;
    std::unordered_map<T, T> parent;

    for (auto [u, V] : adjList)
    {
        dist[u] = INT_MAX;
    }
    dist[s] = 0;

    buckets[0].insert(s);

    for (int i = 0; i < maxWeight; i++)
    {
        // Iterating over all buckets
        // i -> means ith bucket
        // ith bucket holds nodes which are i units away from s

        while (!buckets[i].empty())
        {
            T u = *buckets[i].begin();
            buckets[i].erase(buckets[i].begin());

            if (i > dist[u])
            {
                continue;
            }

            for (auto [v, w] : adjList[u])
            {
                if ((dist[u] + w) < dist[v])
                {
                    if (dist[v] != INT_MAX)
                    {
                        buckets[dist[v]].erase(v);
                    }

                    dist[v] = dist[u] + w;
                    buckets[dist[v]].insert(v);
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