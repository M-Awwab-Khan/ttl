#include <bits/stdc++.h>
#include "Graph.h"

using namespace std;

int main()
{
    Graph<char> g(true, true);

    vector<char> vertices = {'A', 'B', 'C', 'S'};

    unordered_map<char, vector<pair<char, int>>> edges;

    edges['S'] = {{'A', 3}, {'B', 6}};
    edges['A'] = {{'B', 5}};
    edges['B'] = {{'C', 2}};
    edges['C'] = {{'A', -10}};

    for (int v : vertices)
    {
        g.addVertex(v);
    }

    for (char v : vertices)
    {
        for (pair<char, int> p : edges[v])
        {
            g.addEdge(v, p.first, p.second);
        }
    }

    g.print();
    g.bellmanFord('S');

    return 0;
}