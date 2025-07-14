#pragma once

#include "Graph.h"

template <typename T>
void Graph<T>::BFS(T s)
{
    std::unordered_set<T> visited;
    std::queue<T> q;
    q.push(s);
    visited.insert(s);
    while (!q.empty())
    {
        T curr = q.front();
        q.pop();
        std::cout << curr << ' ';

        for (std::pair<T, int> p : adjList[curr])
        {
            if (visited.find(p.first) == visited.end())
            {
                visited.insert(p.first);
                q.push(p.first);
            }
        }
    }
    std::cout << '\n';
}

// For Complete BFS
template <typename T>
void Graph<T>::BFS(T s, std::unordered_set<T> &visited)
{
    std::queue<T> q;
    q.push(s);
    visited.insert(s);
    while (!q.empty())
    {
        T curr = q.front();
        q.pop();
        visited.insert(curr);
        std::cout << curr << ' ';

        for (std::pair<T, int> p : adjList[curr])
        {
            if (visited.find(p.first) == visited.end())
            {
                q.push(p.first);
                visited.insert(p.first);
            }
        }
    }
}

template <typename T>
void Graph<T>::BFSComplete()
{
    std::unordered_set<T> visited;
    // queue<T> q;

    for (auto [u, V] : adjList)
    {
        if (visited.find(u) == visited.end())
        {
            BFS(u, visited);
        }
    }

    std::cout << '\n';
}
