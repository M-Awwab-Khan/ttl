#include <bits/stdc++.h>
#include "Graph.h"

int main()
{
    Graph g(true, true, 6);

    vector<int> vertices = {0, 1, 2, 3, 4, 5};

    vector<vector<pair<int, int>>> edges(vertices.size());

    edges[0] = {{1, 16}, {2, 13}};
    edges[1] = {{3, 12}, {2, 10}};
    edges[2] = {{1, 4}, {4, 14}};
    edges[3] = {{2, 9}, {5, 20}};
    edges[4] = {{3, 7}, {5, 4}};
    edges[5] = {};

    int id = 0;
    for (int v : vertices)
    {
        for (pair<int, int> p : edges[v])
        {
            g.addEdge(v, p.first, p.second, id);
            id++;
        }
    }

    g.maxFlowRelabel(0, 5);

    return 0;
}