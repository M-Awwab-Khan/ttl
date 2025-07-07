#pragma once

#include "Graph.h"

/*
Solved Problems:
1. https://codeforces.com/problemset/problem/2044/G1
2. https://atcoder.jp/contests/dp/tasks/dp_g?lang=en
*/

template <typename T>
void Graph<T>::DFSHelper(T s, std::unordered_set<T> &visited, bool print)
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
            DFSHelper(p.first, visited, print);
        }
    }
}

template <typename T>
void Graph<T>::DFS(T s)
{
    std::unordered_set<T> visited;
    DFSHelper(s, visited);
    std::cout << '\n';
}

template <typename T>
void Graph<T>::DFSComplete()
{
    std::unordered_set<T> visited;

    for (auto [u, V] : adjList)
    {
        for (std::pair<T, int> p : V)
        {
            if (visited.find(p.first) == visited.end())
            {
                DFSHelper(p.first, visited);
            }
        }
    }

    std::cout << '\n';
}