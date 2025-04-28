# include <bits/stdc++.h>
# include "Graph.h"

using namespace std;

int main() {

    Graph<int> g(false, false);


    vector<int> vertices = {0, 1, 2, 3, 4, 5, 6, 7, 8};

    unordered_map< int, vector< pair<int, int> > > edges;
    edges[0] = { {1, 0}, {5, 0}, {6, 0} };
    edges[1] = { {2, 0}, {3,  0}, {4, 0} };
    edges[2] = { {3, 0} };
    edges[3] = { };
    edges[4] = { {5, 0} };
    edges[5] = { };
    edges[6] = { {7, 0}, {8, 0} };
    edges[7] = { {8, 0} };


    for(int v: vertices) {g.addVertex(v);}

    for(int v: vertices) {
        for(pair<int, int> p: edges[v]) {
            g.addEdge(v, p.first, p.second);
        }
    }

    g.getArticulationPoints();

    return 0;
}