#pragma once
#include "Graph.h"

template <typename T>
void Graph<T>::shortestPathBFS(T s, T e)
{
    std::unordered_map<T, T> parent;
    std::unordered_set<T> visited;

    parent[s] = s;
    std::queue<T> q;
    q.push(s);
    visited.insert(s);
    T curr, next;

    while (!q.empty())
    {
        curr = q.front();
        q.pop();
        if (curr == e)
        {
            break;
        }

        for (std::pair<T, int> p : adjList[curr])
        {
            next = p.first;
            if (visited.find(next) == visited.end())
            {
                q.push(next);
                visited.insert(next);
                parent[next] = curr;
            }
        }
    }

    if (parent.find(e) != parent.end())
    {
        std::vector<T> path;
        T curr = e;
        while (true)
        {
            path.push_back(curr);
            if (curr == parent[curr])
            {
                break;
            }
            curr = parent[curr];
        }

        for (int i = path.size() - 1; i >= 0; i--)
        {
            std::cout << path[i] << ' ';
        }
        std::cout << '\n';
    }
    else
    {
        std::cout << "Path Doesn't Exist\n";
    }
}