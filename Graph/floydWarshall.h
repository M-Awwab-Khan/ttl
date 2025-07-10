#pragma once

#include "Graph.h"

template <typename T>
void Graph<T>::floydWarshall()
{
    int POSINF = INT_MAX;
    int NEGINF = INT_MIN;
    std::unordered_map<T, std::unordered_map<T, int>> dist;
    std::unordered_map<T, std::unordered_map<T, T>> parent;
    // Setting distances to INF

    for (auto [i, a] : adjList)
    {
        for (auto [j, b] : adjList)
        {
            if (i == j)
            {
                dist[i][j] = 0;
                parent[i][j] = i;
            }
            else
            {
                dist[i][j] = POSINF;
            }
        }
    }

    for (auto [i, v] : adjList)
    {
        for (auto [j, w] : adjList[i])
        {
            if (w < dist[i][j])
            {
                dist[i][j] = w;
                parent[i][j] = i;
            }
        }
    }
    // Distance Populated

    for (auto [k, a] : adjList)
    {
        for (auto [i, b] : adjList)
        {
            for (auto [j, c] : adjList)
            {
                // i to j THROUGH k
                // (i, j) => (i, k) + (k, j)
                if ((dist[i][k] < POSINF) && (dist[k][j] < POSINF))
                {
                    // Reachable
                    if ((dist[i][k] + dist[k][j]) < dist[i][j])
                    {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        parent[i][j] = k;
                    }
                    dist[i][j] = max(dist[i][j], NEGINF); // To avoid decreasing than -ve INF
                }
            }
        }
    }

    std::cout << "Shortest Distance\n";
    for (auto [i, a] : adjList)
    {
        for (auto [j, b] : adjList)
        {
            std::cout << i << " -> " << j << ": " << dist[i][j] << '\n';
        }
    }

    std::cout << "Shortest Path\n";
    for (auto [i, a] : adjList)
    {
        for (auto [j, b] : adjList)
        {
            for (T u : constructPath(j, i, parent))
            {
                std::cout << u << ' ';
            }
            std::cout << '\n';
        }
    }
}