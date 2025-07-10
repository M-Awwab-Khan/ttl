#pragma once

#include "Graph.h"

/*

Without DSU -> O(N^2 + M LOGN)

WITH DSU -> O(M LOGN)

*/

// DSU

vector<int> parent, dsuRank;

void makeSet(int i)
{
    parent[i] = i;
    dsuRank[i] = 0;
}

int findSet(int i)
{
    if (i == parent[i])
    {
        return i;
    }
    return parent[i] = findSet(parent[i]);
}

void unionSets(int a, int b)
{
    a = findSet(a);
    b = findSet(b);
    if (a != b)
    {
        if (dsuRank[a] < dsuRank[b])
        {
            swap(a, b);
        }
        parent[b] = a;
        if (dsuRank[a] == dsuRank[b])
        {
            dsuRank[a]++;
        }
    }
}

// DSU

void Graph::MSTKruskalsAlgo()
{
    parent.resize(n);
    dsuRank.resize(n);

    vector<Edge> edges;
    vector<Edge> result;
    int totalWeight = 0;
    for (int i = 0; i < n; i++)
    {
        makeSet(i);
        for (Edge e : adjList[i])
        {
            edges.push_back(e);
        }
    }

    sort(edges.begin(), edges.end());

    for (Edge e : edges)
    {
        if (findSet(e.u) != findSet(e.v))
        {
            result.push_back(e);
            totalWeight += e.w;
            unionSets(e.u, e.v);
        }
    }
    cout << "MST COST = " << totalWeight << '\n';
    for (Edge e : result)
    {
        cout << e.u << ' ' << e.v << '\n';
    }
}