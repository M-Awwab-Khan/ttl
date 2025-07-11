#pragma once

#include "Graph.h"

vector<int> level, ptr;

int bfs(int s, int t, int n, vector<vector<Edge>> &adjList)
{
    fill(level.begin(), level.begin() + n, -1);
    queue<int> q;
    q.push(s);
    level[s] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (Edge e : adjList[u])
        {
            if (e.w > 0 && level[e.v] == -1)
            {
                level[e.v] = level[e.u] + 1;
                q.push(e.v);
            }
        }
    }

    return level[t] != -1;
}

int dinicDfs(int u, int t, int pushed, vector<vector<Edge>> &adjList)
{
    if (u == t || pushed == 0)
    {
        return 0;
    }
    for (int &id = ptr[u]; id < adjList[u].size(); id++)
    {
        Edge e = adjList[u][id];
        if (level[e.v] == level[e.u] + 1 && e.w > 0)
        {
            int newPushed = dinicDfs(e.v, t, min(pushed, e.w), adjList);
            if (newPushed > 0)
            {
                e.w -= newPushed;
                adjList[e.v][e.u].w += newPushed;
                return newPushed;
            }
        }
    }
    return 0;
}

void Graph::maxFlowDinic(int s, int t)
{
    level.resize(n, -1);
    ptr.resize(n, 0);
    int pushed;
    int flow = 0;
    while (bfs(s, t, n, adjList))
    {
        fill(ptr.begin(), ptr.begin() + n, 0);
        while (pushed = dinicDfs(s, t, INT_MAX, adjList))
        {
            flow += pushed;
        }
    }

    cout << "MAX FLOW: " << flow << '\n';
    cout << "MAX FLOW OF EDGES\n";
    for (int i = 0; i < n; i++)
    {
        for (Edge e : adjList[i])
        {
            cout << e.u << " -> " << e.v << ": " << max(0, adjList[e.u][e.v].w) << '\n';
        }
    }
}