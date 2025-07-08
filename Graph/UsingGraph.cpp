#include <bits/stdc++.h>
#include "Graph.h"

using namespace std;

int main()
{
    Graph<int> g(false, false);

    vector<int> vertices = {1, 2, 3, 4, 5, 6, 7};

    unordered_map<int, vector<pair<int, int>>> edges;

    edges[1] = {{4, 0}, {7, 0}};
    edges[2] = {{6, 0}, {5, 0}};
    edges[3] = {{4, 0}, {5, 0}, {7, 0}};
    edges[4] = {{7, 0}};
    edges[5] = {{6, 0}};
    edges[6] = {};
    edges[7] = {};

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

    std::unordered_map<int, std::vector<std::pair<int, int>>> adjList = g.getStrongOrientation();

    for (auto [u, V] : adjList)
    {
        for (auto [v, w] : V)
        {
            cout << u << ' ' << v << '\n';
        }
    }

    return 0;
}