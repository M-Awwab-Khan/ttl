#pragma once
#include "Graph.h"

template <typename T>
void Graph<T>::bellmanFord(T s)
{
    std::unordered_map<T, int> dist;
    for (auto [k, v] : adjList)
    {
        dist[k] = INT_MAX;
    }
    dist[s] = 0;

    for (int i = 0; i < vertices - 1; i++)
    {
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
                }
            }
        }
    }

    for (int i = 0; i < vertices - 1; i++)
    {
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
                }
            }
        }
    }

    std::cout << "Shortest Distance\n";
    for (auto [k, v] : adjList)
    {
        std::cout << k << ": " << dist[k] << '\n';
    }
}
