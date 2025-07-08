#pragma once

#include "Graph.h"

// For Priority Queue
template <typename T>
class Compare
{
public:
    bool operator()(std::pair<T, int> p1, std::pair<T, int> p2);
};

template <typename T>
bool Compare<T>::operator()(std::pair<T, int> p1, std::pair<T, int> p2)
{
    return p1.second > p2.second;
}

template <typename T>
T Graph<T>::min(T &a, T &b)
{
    if (a < b)
    {
        return a;
    }
    return b;
}

template <typename T>
Graph<T>::Graph(bool d, bool w)
{
    directed = d;
    weighted = w;
}

template <typename T>
void Graph<T>::addVertex(T v)
{
    adjList[v] = {};
    vertices++;
}

template <typename T>
void Graph<T>::addEdge(T u, T v, int W)
{
    adjList[u].push_back(std::make_pair(v, W));
    if (!directed)
    {
        adjList[v].push_back(std::make_pair(u, W));
    }
}

template <typename T>
void Graph<T>::print()
{
    for (auto [u, V] : adjList)
    {
        std::cout << u << ": ";
        for (std::pair<T, int> p : V)
        {
            if (weighted)
            {
                std::cout << "{ " << p.first << ", " << p.second << " } ";
            }
            else
            {
                std::cout << p.first << ' ';
            }
        }
        std::cout << '\n';
    }
}

#include "DFS.h"
#include "BFS.h"
#include "connectedComponents.h"
#include "dijkstra.h"
#include "shortestPathBFS.h"
#include "topsort.h"
#include "bellmanFord.h"
#include "articulationPoints.h"
#include "bridges.h"
#include "stronglyConnectedComponents.h"
#include "strongOrientation.h"