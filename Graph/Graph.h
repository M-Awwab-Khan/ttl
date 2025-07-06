#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <utility>

// T -> Vertices

template <typename T>
class Graph
{
private:
    bool directed = false;
    bool weighted = false;
    int vertices = 0;

    std::unordered_map<T, std::vector<std::pair<T, int>>> adjList;

    void DFSHelper(T s, std::unordered_set<T> &visited, bool print = true);

    void DFSForConnectedComponents(T s, std::unordered_set<T> &visited, bool print = true);

    void DFSForBridge(T u, std::unordered_map<T, int> &disc, std::unordered_map<T, int> &low, std::unordered_map<T, T> &parent, std::unordered_set<std::pair<T, T>> &bridges);

    void DFSForArticulationPoints(T u, std::unordered_map<T, int> &disc, std::unordered_map<T, T> &parent, std::unordered_map<T, int> &low, std::unordered_set<T> &articulationPoints);

    T min(T &a, T &b);

public:
    Graph(bool d = false, bool w = false);

    void addVertex(T v);

    void addEdge(T u, T v, int W = 0);

    void print();

    void DFS(T s);

    void DFSComplete();

    void BFS(T s);

    void BFSComplete();

    void BFS(T s, std::unordered_set<T> &visited);

    void dijkstra(T s);

    int connectedComponents();

    void shortestPathBFS(T s, T e);

    void topSortHelper(std::unordered_set<T> &visited, T s, int &i, std::unordered_map<T, int> &res);

    // Works for only Directed Graph with no Cycle
    std::unordered_map<T, int> topSort();

    void bellmanFord(T s);

    std::unordered_set<T> getArticulationPoints();

    std::vector<std::pair<T, T>> getBridges();
};

#include "GraphImplementation.h"

#endif