#pragma once

#include "Graph.h"

/*
Given an undirected, Weighted Graph
Output the tree with minimum cost of edges.

1. Dense Grpahs -> O(N^2)
using ADJACENY MATRIX

2. Sparse Graphs -> O(N + M LOG N)
using ADJACENCY MATRIX + SET

*/

void Graph::MSTPrimsAlgo(bool dense)
{
    vector<bool> selected(n, false);
    vector<Edge> minEdge(n);
    vector<Edge> result;
    for (int i = 0; i < n; i++)
    {
        minEdge[i] = Edge(0, i, -1, INT_MAX);
    }
    int totalWeight = 0;
    minEdge[0] = Edge(0, 0, -1, 0);

    if (dense)
    {
        for (int i = 0; i < n; ++i)
        {
            int u = -1;
            for (int j = 0; j < n; ++j)
            {
                if (!selected[j] && (u == -1 || minEdge[j].w < minEdge[u].w))
                    u = j;
            }

            if (minEdge[u].w == INT_MAX)
            {
                cout << "No MST!" << endl;
                return;
            }

            selected[u] = true;
            totalWeight += minEdge[u].w;
            if (minEdge[u].v != -1)
                result.push_back(Edge(0, u, minEdge[u].v, minEdge[u].w));

            for (int v = 0; v < n; v++)
            {
                if (adjMatrix[u][v].w < minEdge[v].w)
                {
                    minEdge[v] = Edge(0, v, u, adjMatrix[u][v].w);
                }
            }
        }
    }
    else
    {
        set<Edge> q;
        q.insert(Edge(0, 0, -1, 0));

        for (int i = 0; i < n; i++)
        {
            if (q.empty())
            {
                cout << "NO MST\n";
                return;
            }

            int u = q.begin()->u;
            selected[u] = true;
            totalWeight += q.begin()->w;
            q.erase(q.begin());

            if (minEdge[u].v != -1)
            {
                result.push_back(Edge(0, u, minEdge[u].v, minEdge[u].w));
            }

            for (Edge e : adjList[u])
            {
                int v = e.v;
                if (!selected[v] && (e.w < minEdge[v].w))
                {
                    q.erase(Edge(0, v, minEdge[v].v, minEdge[v].w));
                    minEdge[v] = Edge(0, v, u, e.w);
                    q.insert(minEdge[v]);
                }
            }
        }
    }

    cout << "MST COST = " << totalWeight << '\n';
    for (Edge e : result)
    {
        cout << e.u << ' ' << e.v << '\n';
    }
}
