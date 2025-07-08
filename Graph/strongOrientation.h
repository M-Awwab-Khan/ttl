#pragma once

#include "Graph.h"
#include <map>
#include <unordered_set>

/*

Given an undirected graph, Orient Thes edges in a way to minimize the SCCs.

Weight Doesn't matter in the usual case.

If a bridge exist in a component of the graph then SCC of the component > 1.

Total Minimum SCCs = DFS Calls + bridgeCount

*/
template <typename T>
void Graph<T>::dfsForStrongOrientation(T u, std::unordered_map<T, int> &disc, std::unordered_map<T, int> &low, std::unordered_map<T, std::vector<std::pair<T, int>>> &newAdjList, std::vector<std::pair<T, T>> &edges, std::unordered_set<int> &visitedEdges, std::unordered_map<T, std::vector<std::pair<T, int>>> &result, int &bridgeCount)
{
    static int time = 0;
    disc[u] = time;
    low[u] = time;
    time++;

    for (auto [v, eId] : newAdjList[u])
    {
        if (visitedEdges.find(eId) != visitedEdges.end())
        {
            continue;
        }
        visitedEdges.insert(eId);

        // Orienting Edge
        result[u].push_back({v, 0});

        // Bridge Detection
        if (disc.find(v) == disc.end())
        {

            dfsForStrongOrientation(v, disc, low, newAdjList, edges, visitedEdges, result, bridgeCount);
            low[u] = min(low[u], low[v]);
            if (low[v] > disc[u])
            {
                bridgeCount++;
            }
        }
        else
        {
            low[u] = min(low[u], disc[v]);
        }
    }
}

template <typename T>
std::unordered_map<T, std::vector<std::pair<T, int>>> Graph<T>::getStrongOrientation()
{
    std::map<std::pair<T, T>, int> edgesToInt; // Not Required, Just to transform the org Adj List

    // Preparing Inputs
    std::vector<std::pair<T, T>> edges;
    std::unordered_map<T, std::vector<std::pair<T, int>>> newAdjList;
    std::unordered_map<T, std::vector<std::pair<T, int>>> result;
    std::unordered_set<int> visitedEdges;
    std::unordered_map<T, int> disc, low;

    int edgeId = 0;
    for (auto [u, V] : adjList)
    {
        for (auto [v, w] : V)
        {
            if (edgesToInt.find({u, v}) == edgesToInt.end())
            {
                edges.push_back({u, v});
                newAdjList[u].push_back({v, edgeId});
                newAdjList[v].push_back({u, edgeId});
                edgesToInt[{u, v}] = edgeId;
                edgesToInt[{v, u}] = edgeId;
                edgeId++;
            }
        }
    }

    int bridgeCount = 0;
    int comp = 0;
    for (auto [u, V] : adjList)
    {
        if (disc.find(u) == disc.end())
        {
            dfsForStrongOrientation(u, disc, low, newAdjList, edges, visitedEdges, result, bridgeCount);
            comp++;
        }
    }

    return result;
}