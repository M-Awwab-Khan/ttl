#pragma once

#include "Graph.h"
#include <deque>

/*
When the weight is only 0 or 1.

*/

template <typename T>
void Graph<T>::BFS01(T s)
{
    std::unordered_map<T, int> dist;
    std::unordered_map<T, T> parent;
    std::deque<T> q;
    for (auto [u, V] : adjList)
    {
        dist[u] = INT_MAX;
    }
    dist[s] = 0;

    q.push_front(s);

    while (!q.empty())
    {
        T u = q.front();
        q.pop_front();

        for (auto [v, w] : adjList[u])
        {
            if ((dist[u] + w) < dist[v])
            {
                dist[v] = dist[u] + w;
                parent[v] = u;
                if (w == 0)
                {
                    q.push_front(v);
                }
                else
                {
                    q.push_back(v);
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