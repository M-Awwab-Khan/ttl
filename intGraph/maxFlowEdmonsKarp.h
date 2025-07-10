#pragma once

#include "Graph.h"

/*
Works only for Integer flows

Given graph is directed

But we make capacity and flow matrices as undirected

Using BFS

Time Complexity is O(V E^2)

*/

int BFS(int s, int t, vector<vector<Edge>> &adjList, vector<int> &parent, vector<vector<int>> &capacity)
{
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INT_MAX});

    while (!q.empty())
    {
        auto [u, flow] = q.front();
        q.pop();

        for (Edge e : adjList[u])
        {
            if (parent[e.v] == -1 && capacity[e.u][e.v])
            {
                parent[e.v] = u;
                int newFlow = min(flow, capacity[e.u][e.v]);
                if (e.v == t)
                {
                    return newFlow;
                }

                q.push({e.v, newFlow});
            }
        }
    }

    return 0;
}

void Graph::maxFlowEdmonsKarp(int s, int t)
{
    vector<int> parent(n, -1);
    vector<vector<int>> capacity(n, vector<int>(n, 0));
    vector<vector<int>> maxEdgeFlow(n, vector<int>(n, 0));
    // Populating Capacity
    for (int i = 0; i < n; i++)
    {
        for (Edge e : adjList[i])
        {
            capacity[e.u][e.v] = e.w;
        }
    }

    int flow = 0;
    int newFlow = 0;
    while (newFlow = BFS(s, t, adjList, parent, capacity))
    {
        flow += newFlow;
        int curr = t;
        while (curr != s)
        {
            int prev = parent[curr];
            capacity[prev][curr] -= newFlow;
            capacity[curr][prev] += newFlow;
            maxEdgeFlow[prev][curr] = max(maxEdgeFlow[prev][curr], newFlow);
            curr = prev;
        }
    }

    cout << "MAX FLOW: " << flow << '\n';
    cout << "MAX FLOW OF EDGES\n";
    for (int i = 0; i < n; i++)
    {
        for (Edge e : adjList[i])
        {
            cout << e.u << " -> " << e.v << ": " << maxEdgeFlow[e.u][e.v] << '\n';
        }
    }
}
