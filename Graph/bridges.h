#pragma once
#include "Graph.h"

template <typename T>
void Graph<T>::DFSForBridge(T u, std::unordered_map<T, int> &disc, std::unordered_map<T, int> &low, std::unordered_map<T, T> &parent, std::unordered_set<std::pair<T, T>> &bridges)
{
    static int time = 0;
    disc[u] = time;
    low[u] = time;
    time++;

    for (auto [v, W] : adjList[u])
    {
        if (disc.find(v) == disc.end())
        {
            parent[v] = u;
            DFSForBridge(v, disc, low, parent, bridges);
            low[u] = min(low[u], low[v]);

            if (low[v] > disc[u])
            {
                bridges.insert({u, v});
            }
        }
        else if (v != parent[u])
        {
            low[u] = min(low[u], disc[v]);
        }
    }
}

template <typename T>
std::vector<std::pair<T, T>> Graph<T>::getBridges()
{
    std::unordered_map<T, int> disc, low;
    std::unordered_map<T, T> parent;
    std::unordered_set<std::pair<T, T>> bridges;

    for (auto &[k, v] : adjList)
    {
        if (disc.find(k) == disc.end())
        {
            DFSForBridge(k, disc, low, parent, bridges);
        }
    }

    std::cout << "BRIDGES\n";
    for (std::pair<T, T> &p : bridges)
    {
        std::cout << p.first << ' ' << p.second << '\n';
    }

    return bridges;
}
