#include <bits/stdc++.h>
#include "Graph.h"

using namespace std;

int main()
{
    Graph<int> g(false, true);

    vector<int> vertices = {1, 2, 3, 4, 5, 6, 7, 8};

    unordered_map<int, vector<pair<int, int>>> edges;

    edges[1] = {{2, 2}, {4, 5}, {3, 4}};
    edges[2] = {{4, 4}, {7, 3}};
    edges[3] = {{4, 3}, {5, 7}};
    edges[4] = {{5, 2}, {6, 3}, {7, 3}};
    edges[5] = {{6, 4}};
    edges[6] = {{8, 2}};
    edges[7] = {{8, 5}};

    for (int v : vertices)
    {
        g.addVertex(v);
    }

    for (int v : vertices)
    {
        for (pair<int, int> p : edges[v])
        {
            g.addEdge(v, p.first, p.second);
        }
    }

    g.dijkstra(1);

    return 0;
}