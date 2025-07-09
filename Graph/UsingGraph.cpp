#include <bits/stdc++.h>
#include "Graph.h"

using namespace std;

int main()
{
    Graph<int> g(true, true);

    vector<int> vertices = {0, 1, 2, 3, 4};

    unordered_map<int, vector<pair<int, int>>> edges;

    edges[0] = {{1, 4}, {3, 5}};
    edges[1] = {{2, 1}, {4, 6}};
    edges[2] = {{0, 2}, {3, 3}};
    edges[3] = {{4, 2}, {2, 1}};
    edges[4] = {{0, 1}, {3, 4}};

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

    g.floydWarshall();

    return 0;
}