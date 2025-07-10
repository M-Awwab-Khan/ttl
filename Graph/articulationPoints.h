#pragma once
#include "Graph.h"

/*
Articulation Points
-> A node such that removing it, increases the connected components.

Conditions:
1. Node U is the root (DFS) and has atleast 2 children (Subgraph).

2. Node U is not the root of DFS tree and it has a child V such that no vertex in subtree rooted with V has a beckedge to one of the ancestors of U.


Checks:
1. Keep the child count of the node, If the child count > 1 then check is it a root.

2. For each node
   We'll keep track of its discovery time and earliest accessible node to get backedge.



**Special**
Don't consider the child to parent edge.
*/

template <typename T>
void Graph<T>::DFSForArticulationPoints(T u, std::unordered_map<T, int> &disc, std::unordered_map<T, T> &parent, std::unordered_map<T, int> &low, std::unordered_set<T> &articulationPoints)
{
    static int time = 0;
    disc[u] = time;
    low[u] = time;
    time++;
    int children = 0;
    for (auto [v, w] : adjList[u])
    {
        if (disc.find(v) == disc.end())
        {
            // Unvisited Node
            children++;
            parent[v] = u;

            DFSForArticulationPoints(v, disc, parent, low, articulationPoints);
            low[u] = min(low[u], low[v]);

            if (parent.find(u) == parent.end() && children > 1)
            {
                // u is Root
                articulationPoints.insert(u);
            }

            if (parent.find(u) != parent.end() && low[v] >= disc[u])
            {
                articulationPoints.insert(u);
            }
        }
        else if (v != parent[u])
        {
            low[u] = min(low[u], disc[v]);
        }
    }
}

template <typename T>
std::unordered_set<T> Graph<T>::getArticulationPoints()
{
    std::unordered_map<T, int> disc, low;
    std::unordered_map<T, T> parent;
    std::unordered_set<T> articulationPoints;

    for (auto [u, v] : adjList)
    {
        if (disc.find(u) == disc.end())
        {
            DFSForArticulationPoints(u, disc, parent, low, articulationPoints);
        }
    }

    std::cout << "Articulation Points:\n";
    for (T u : articulationPoints)
    {
        std::cout << u << ' ';
    }
    std::cout << '\n';
    return articulationPoints;
}
