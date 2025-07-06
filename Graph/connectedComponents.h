#pragma once

#include "Graph.h"

template <typename T>
void Graph<T>::DFSForConnectedComponents(T s, std::unordered_set<T> &visited, bool print)
{
    visited.insert(s);
    if (print)
    {
        std::cout << s << ' ';
    }

    for (std::pair<T, int> p : adjList[s])
    {
        if (visited.find(p.first) == visited.end())
        {
            DFSForConnectedComponents(p.first, visited, print);
        }
    }
}

template <typename T>
int Graph<T>::connectedComponents()
{
    int count = 0;

    std::unordered_set<T> visited;
    for (auto [k, v] : adjList)
    {
        if (visited.find(k) == visited.end())
        {
            count++;
            DFSForConnectedComponents(k, visited, false);
        }
    }

    return count;
}
