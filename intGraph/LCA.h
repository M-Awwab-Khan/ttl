#pragma once

#include "Graph.h"

vector<int> timeIn, timeOut;
vector<vector<int>> up;
int l;

void dfs(int u, int p, int time, vector<vector<Edge>> &adjList)
{
    timeIn[u] = time++;
    up[u][0] = p;
    for (int i = 1; i <= l; i++)
    {
        up[u][i] = up[up[u][i - 1]][i - 1];
    }

    for (Edge e : adjList[u])
    {
        if (e.v != p)
        {
            dfs(e.v, u, time, adjList);
        }
    }

    timeOut[u] = time++;
}

bool isAncestor(int u, int v)
{
    return timeIn[u] <= timeIn[v] && timeOut[u] >= timeOut[v];
}

int getLCA(int u, int v)
{
    if (isAncestor(u, v))
    {
        return u;
    }
    if (isAncestor(v, u))
    {
        return v;
    }
    for (int i = l; i >= 0; i--)
    {
        if (!isAncestor(up[u][i], v))
        {

            u = up[u][i];
        }
    }

    return up[u][0];
}

void Graph::LCA(vector<pair<int, int>> &queries)
{
    timeIn.resize(n);
    timeOut.resize(n);
    l = ceil(log2(n));
    up.assign(n, vector<int>(l + 1));

    int time = 1;
    dfs(0, 0, time, adjList);

    for (auto [a, b] : queries)
    {
        cout << "LCA of " << a << " and " << b << ": " << getLCA(a, b) << '\n';
    }
}