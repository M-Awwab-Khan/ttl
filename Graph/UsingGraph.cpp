#include <bits/stdc++.h>
#include "Graph.h"

using namespace std;

int main()
{
    Graph<int> g(false, true);

    vector<int> vertices = {0, 1, 2, 3, 4, 5, 6, 7, 8};

    unordered_map<int, vector<pair<int, int>>> edges;

    edges[0] = {{1, 4}, {7, 8}};
    edges[1] = {{2, 8}, {7, 11}};
    edges[2] = {{3, 7}, {8, 2}};
    edges[3] = {{4, 9}, {5, 14}};
    edges[4] = {{5, 10}};
    edges[5] = {{6, 2}};
    edges[6] = {{7, 1}, {8, 6}};
    edges[7] = {{8, 7}};

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

    g.kBFS_DialsAlgo(0, 14);

    return 0;
}