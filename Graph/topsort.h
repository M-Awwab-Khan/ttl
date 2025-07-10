#pragma once
#include "Graph.h"

/*
Works only for Directed Acyclic Graphs (DAG).
*/

template <typename T>
void Graph<T>::topSortHelper(std::unordered_set<T> &visited, T s, int &i, std::unordered_map<T, int> &res)
{
    visited.insert(s);
    for (auto p : adjList[s])
    {
        if (visited.find(p.first) == visited.end())
        {
            topSortHelper(visited, p.first, i, res);
        }
    }
    res[s] = i--;
}

template <typename T>
std::unordered_map<T, int> Graph<T>::topSort()
{
    int i = vertices - 1;
    std::unordered_map<T, int> result;
    std::unordered_set<T> visited;

    for (auto [k, v] : adjList)
    {
        if (visited.find(k) == visited.end())
        {
            topSortHelper(visited, k, i, result);
        }
    }

    return result;
}
