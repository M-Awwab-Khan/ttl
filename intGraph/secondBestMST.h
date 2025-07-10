#pragma once

#include "Graph.h"

/*

1. Using Kruskals Algo in O(VE)

Calculate MST.

For each edge e in MST (TOTAL n - 1)
    Ban this edge, And calculate MST again.
    You don't have to sort the array again, just reset DSU and pick edges


2. Using LCA with binary lifting in O(E LOG V)

*/

void Graph::secondBestMST()
{
    // BHT Mushkil hai bhai
}