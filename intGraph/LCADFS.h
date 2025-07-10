#pragma once

#include "Graph.h"

// Answers All Queries in O(N + M)

// DSU
vector<int> parents, dsuRank;

void makeSet(int a)
{
    parents[a] = a;
    dsuRank[a] = 0;
}

int findSet(int a)
{
    if (a == parent[a])
    {
        return a;
    }
    return parent[a] = findSet(parent[a]);
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
        parents[b] = a;
        if (dsuRank[a] == dsuRank[b])
        {
            dsuRank[a]++;
        }
    }
}

// DSU

vector<int> ancestors, visited;

void dfs(int u, vector<vector<Edge>> &adjList, vector<vector<int>> &queries)
{
    visited[u] = 1;
    ancestors[u] = u;
    for (Edge e : adjList[u])
    {
        if (visited[e.v] == 0)
        {
            dfs(e.v, adjList, queries);
            unionSets(u, e.v);
            ancestors[findSet(u)] = u;
        }
    }

    for (int v : queries[u])
    {
        if (visited[v] == 1)
        {
            cout << "LCA of " << u << " and " << v << " is " << ancestors[findSet(v)] << ".\n";
        }
    }
}

void Graph::LCADFS(vector<pair<int, int>> &queries)
{
    parents.resize(n);
    dsuRank.resize(n);
    for (int i = 0; i < n; i++)
    {
        makeSet(i);
    }

    ancestors.resize(n);
    visited.resize(n, 0);

    vector<vector<int>> adjQueries(n);

    for (auto [a, b] : queries)
    {
        adjQueries[a].push_back(b);
    }

    dfs(0, adjList, adjQueries);
}