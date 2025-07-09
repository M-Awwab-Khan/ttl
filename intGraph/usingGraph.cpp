#include <bits/stdc++.h>
#include "Graph.h"

int main()
{
    Graph g(false, true, 9);

    vector<int> vertices = {0, 1, 2, 3, 4, 5, 6, 7, 8};

    vector<vector<pair<int, int>>> edges(vertices.size());

    edges[0] = {{1, 4}, {7, 8}};
    edges[1] = {{2, 8}, {7, 11}};
    edges[2] = {{3, 7}, {8, 2}, {5, 4}};
    edges[3] = {{4, 9}, {5, 14}};
    edges[4] = {{5, 10}};
    edges[5] = {{6, 2}};
    edges[6] = {{7, 1}, {8, 6}};
    edges[7] = {{8, 7}};

    int id = 0;
    for (int v : vertices)
    {
        for (pair<int, int> p : edges[v])
        {
            g.addEdge(v, p.first, p.second, id);
            id++;
        }
    }

    g.MSTPrimsAlgo(false);

    return 0;
}