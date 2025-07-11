#pragma once

#include "Graph.h"

/*

Given directed graph but we make it as undirected

T.C = O(V^3)

*/

vector<vector<int>> capacity, edgeFlow;
vector<int> height, excess;

void push(int u, int v)
{
    // Height[u] > Height[v]
    int d = min(excess[u], capacity[u][v] - edgeFlow[u][v]);
    edgeFlow[u][v] += d;
    edgeFlow[v][u] -= d;
    excess[u] -= d;
    excess[v] += d;
}

void relabel(int u, int n)
{
    int d = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        if (capacity[u][i] - edgeFlow[u][i] > 0)
        {
            d = min(d, height[i]);
        }
    }
    if (d < INT_MAX)
    {
        height[u] = d + 1;
    }
}

vector<int> findMaxHeight(int s, int t, int n)
{
    vector<int> maxHeight;
    for (int i = 0; i < n; i++)
    {
        if (i != s && i != t && excess[i] > 0)
        {
            if (!maxHeight.empty() && height[i] > height[maxHeight[0]])
            {
                maxHeight.clear();
            }
            if (maxHeight.empty() || height[i] == height[maxHeight[0]])
            {
                maxHeight.push_back(i);
            }
        }
    }
    return maxHeight;
}

void Graph::maxFlowRelabel(int s, int t)
{

    // Populating capacity and edgeFlow
    capacity.resize(n, vector<int>(n, 0));
    edgeFlow.resize(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++)
    {
        for (Edge e : adjList[i])
        {
            capacity[e.u][e.v] = e.w;
        }
    }

    height.resize(n, 0);
    height[s] = n;

    excess.resize(n, 0);
    excess[s] = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        if (i != s)
        {
            push(s, i);
        }
    }

    vector<int> current;
    while (!(current = findMaxHeight(s, t, n)).empty())
    {
        for (int i : current)
        {
            bool pushed = false;
            for (int j = 0; j < n && excess[i]; j++)
            {
                if (capacity[i][j] - edgeFlow[i][j] > 0 && height[i] == height[j] + 1)
                {
                    push(i, j);
                    pushed = true;
                }
            }
            if (!pushed)
            {
                relabel(i, n);
                break;
            }
        }
    }

    cout << "MAX FLOW: " << excess[t] << '\n';
    cout << "MAX FLOW OF EDGES\n";
    for (int i = 0; i < n; i++)
    {
        for (Edge e : adjList[i])
        {
            cout << e.u << " -> " << e.v << ": " << max(0, edgeFlow[e.u][e.v]) << '\n';
        }
    }
}