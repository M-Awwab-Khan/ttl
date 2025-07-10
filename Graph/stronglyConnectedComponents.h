#pragma once

#include "Graph.h"
#include <algorithm>

template <typename T>
void Graph<T>::tarjansAlgoForSCC(T u, std::unordered_map<T, int> &disc, std::unordered_map<T, int> &low, std::unordered_map<T, bool> &isInStack, std::vector<std::vector<T>> &SCC, int &sccCount)
{
    static int time = 1;
    disc[u] = time;
    low[u] = time;
    time++;
    isInStack[u] = true;
    T v;
    for (std::pair<T, int> p : adjList[u])
    {
        v = p.first;
        if (disc.find(v) == disc.end())
        {
            tarjansAlgoForSCC(v, disc, low, isInStack, SCC, sccCount);
            low[u] = min(low[u], low[v]);
        }
        else if (isInStack[v])
        {
            // Backedge
            low[u] = min(low[u], disc[v]);
        }
    }

    if (SCC.size() == sccCount)
    {
        SCC.push_back({});
    }
    SCC[sccCount].push_back(u);
    if (low[u] == disc[u])
    {
        // u is the root of SCC
        std::cout << "ROOT: " << u << '\n';
        sccCount++;
    }

    isInStack[u] = false;
}

template <typename T>
void Graph<T>::kosarajuAlgoForSCC(T u, std::unordered_map<T, std::vector<std::pair<T, int>>> &adjList, std::unordered_set<T> &visited, std::vector<T> &output)
{
    visited.insert(u);

    for (std::pair<T, int> p : adjList[u])
    {
        if (visited.find(p.first) == visited.end())
        {
            kosarajuAlgoForSCC(p.first, adjList, visited, output);
        }
    }

    output.push_back(u);
}

template <typename T>
std::vector<std::vector<T>> Graph<T>::getStronglyConnectedComponents(bool tarjansAlgo)
{

    std::vector<std::vector<T>> SCC;
    if (tarjansAlgo)
    {
        std::unordered_map<T, int> disc, low;
        std::unordered_map<T, bool> isInStack;
        int sccCount = 0;

        for (auto [u, V] : adjList)
        {
            if (disc[u] == 0)
            {
                tarjansAlgoForSCC(u, disc, low, isInStack, SCC, sccCount);
            }
        }
    }
    else
    {
        std::unordered_set<T> visited;
        std::vector<T> order;
        for (auto [u, V] : adjList)
        {
            if (visited.find(u) == visited.end())
            {
                kosarajuAlgoForSCC(u, adjList, visited, order);
            }
        }

        std::reverse(order.begin(), order.end());

        std::unordered_map<T, std::vector<std::pair<T, int>>> revAdjList;

        for (auto [u, V] : adjList)
        {
            for (auto [v, w] : V)
            {
                revAdjList[v].push_back({u, w});
            }
        }

        visited.clear();
        for (T u : order)
        {
            if (visited.find(u) == visited.end())
            {
                std::vector<T> comp;
                kosarajuAlgoForSCC(u, revAdjList, visited, comp);
                SCC.push_back(comp);
            }
        }
    }

    std::cout << "Strongly Connected Components:\n";
    for (std::vector<T> V : SCC)
    {
        for (T u : V)
        {
            std::cout << u << ' ';
        }

        std::cout << '\n';
    }

    return SCC;
}