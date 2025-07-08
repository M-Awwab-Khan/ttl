#include <bits/stdc++.h>
#include "Graph.h"

using namespace std;

int main()
{
    Graph<int> g(true, false);

    vector<int> vertices = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    unordered_map<int, vector<pair<int, int>>> edges;
    edges[0] = {{1, 0}, {7, 0}};
    edges[1] = {{1, 0}, {2, 0}};
    edges[2] = {{1, 0}, {5, 0}};
    edges[3] = {{2, 0}, {4, 0}};
    edges[4] = {{9, 0}};
    edges[5] = {{6, 0}, {3, 0}, {9, 0}};
    edges[6] = {{2, 0}};
    edges[7] = {{0, 0}, {6, 0}, {8, 0}};
    edges[8] = {{6, 0}};
    edges[9] = {{4, 0}};

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

    g.getStronglyConnectedComponents(true);

    return 0;
}