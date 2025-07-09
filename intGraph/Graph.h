#ifndef GRAPH_H
#define GRAPH_H

#include <bits/stdc++.h>
using namespace std;

struct Edge
{
public:
    int u = -1, v = -1, w, id;
    Edge() {}
    Edge(int id, int u, int v, int w) : id(id), u(u), v(v), w(w) {}

    // For SET
    bool operator<(const Edge other) const
    {
        return w < other.w;
    }
};

class Graph
{
private:
    int n;
    vector<vector<Edge>> adjList;
    vector<vector<Edge>> adjMatrix;
    bool directed;
    bool weighted;

public:
    Graph(bool d = false, bool w = false, int pn = 0)
    {
        directed = d;
        weighted = w;
        n = pn;
        adjList.resize(n, vector<Edge>());
        adjMatrix.resize(n, vector<Edge>(n, Edge(-1, -1, -1, weighted ? INT_MAX : 0)));
    }

    void addVertex()
    {
        adjList.push_back(adjList.back());
        adjMatrix.push_back(adjMatrix.back());
    }

    void addEdge(int u, int v, int w, int id)
    {

        adjList[u].push_back(Edge(id, u, v, w));
        if (!directed)
        {
            adjList[v].push_back(Edge(id, v, u, w));
        }

        if (weighted)
        {
            adjMatrix[u][v] = Edge(id, u, v, w);
            if (!directed)
            {
                adjMatrix[v][u] = Edge(id, v, u, w);
            }
        }
        else
        {
            adjMatrix[u][v] = Edge(id, u, v, 1);
            if (!directed)
            {
                adjMatrix[v][u] = Edge(id, v, u, 1);
            }
        }
    }

    void MSTPrimsAlgo(bool dense);
};

#include "GraphImplementation.h"

#endif