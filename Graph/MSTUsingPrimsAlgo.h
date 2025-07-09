#pragma once

#include "Graph.h"
#include <set>

/*
Given an undirected, Weighted Graph
Output the tree with minimum cost of edges.

1. Dense Grpahs -> O(N^2)
using ADJACENY MATRIX

2. Sparse Graphs -> O(N + M LOG N)
using ADJACENCY MATRIX + SET

*/
const int INF = INT_MAX;

template <typename T>
struct Edge
{
public:
    int w = INF;
    T v;
    Edge() {}
    Edge(int w, T v) : w(w), v(v) {}

    // For SET
    bool operator<(const Edge other) const
    {
        return std::make_pair(w, v) < std::make_pair(other.w, other.v);
    }
};

template <typename T>
void Graph<T>::MSTUsingPrimsAlgo(bool dense)
{

    int totalWeight = 0;
    std::unordered_map<T, bool> selected;
    std::unordered_map<T, Edge<T>> minEdge;
    for (auto [k, v] : adjList)
    {
        minEdge[k] = Edge<T>(INT_MAX, invalidNode);
        selected[k] = false;
    }

    std::vector<std::pair<T, T>> result;

    // Selecting Arbitrary Edge;
    minEdge[adjList.begin()->first].w = 0;

    if (dense)
    {
        // Using Adjacency Matrix

        for (int i = 0; i < vertices; i++)
        {
            T u = adjMat.begin()->first;
            for (auto [v, a] : adjMat)
            {
                if (!selected[v] && (minEdge[v].w < minEdge[u].w))
                {
                    u = v;
                }
            }

            if (minEdge[u].w == INF)
            {
                std::cout << "NO MST\n";
                return;
            }

            selected[u] = true;
            totalWeight += minEdge[u].w;
            if (minEdge[u].v != invalidNode)
            {
                std::cout << u << ' ' << minEdge[u].v << ' ' << invalidNode << '\n';
                result.push_back({u, minEdge[u].v});
            }

            for (auto [v, a] : adjMat)
            {
                if (adjMat[u][v] < minEdge[v].w)
                {
                    minEdge[v] = {adjMat[u][v], u};
                }
            }
        }
    }
    else
    {
        // Sparse Graphs
        std::set<Edge<T>> q;
        q.insert({0, adjList.begin()->first});

        for (int i = 0; i < vertices; i++)
        {
            if (q.empty())
            {
                std::cout << "NO MST\n";
                return;
            }

            T u = q.begin()->v;
            selected[u] = true;
            totalWeight += q.begin()->w;
            q.erase(q.begin());

            if (minEdge.find(u) != minEdge.end())
            {
                result.push_back({u, minEdge[u].v});
            }

            for (auto [v, w] : adjList[u])
            {
                if (!selected[v] && (w < minEdge[v].w))
                {
                    q.erase({minEdge[v].w, v});
                    minEdge[v] = {w, u};
                    q.insert({w, v});
                }
            }
        }
    }

    std::cout << "MST COST = " << totalWeight << '\n';
    for (auto [u, v] : result)
    {
        std::cout << u << ' ' << v << '\n';
    }
}