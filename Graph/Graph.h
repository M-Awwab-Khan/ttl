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

    void tarjansAlgoForSCC(T u, std::unordered_map<T, int> &disc, std::unordered_map<T, int> &low, std::unordered_map<T, bool> &isInStack, std::vector<std::vector<T>> &SCC, int &sccCount);

    void kosarajuAlgoForSCC(T u, std::unordered_map<T, std::vector<std::pair<T, int>>> &adjList, std::unordered_set<T> &visited, std::vector<T> &output);

    void dfsForStrongOrientation(T u, std::unordered_map<T, int> &disc, std::unordered_map<T, int> &low, std::unordered_map<T, std::vector<std::pair<T, int>>> &newAdjList, std::vector<std::pair<T, T>> &edges, std::unordered_set<int> &visitedEdges, std::unordered_map<T, std::vector<std::pair<T, int>>> &result, int &bridgeCount);

    T min(T &a, T &b);

    T max(T &a, T &b);

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

    void dijkstra(T s, bool denseGraph = false);

    int connectedComponents();

    void shortestPathBFS(T s, T e);

    void topSortHelper(std::unordered_set<T> &visited, T s, int &i, std::unordered_map<T, int> &res);

    // Works for only Directed Graph with no Cycle
    std::unordered_map<T, int> topSort();

    void bellmanFord(T s);

    std::unordered_set<T> getArticulationPoints();

    std::vector<std::pair<T, T>> getBridges();

    std::vector<std::vector<T>> getStronglyConnectedComponents(bool tarjansAlgo = true);

    std::unordered_map<T, std::vector<std::pair<T, int>>> getStrongOrientation();

    std::vector<T> constructPath(T e, T s, std::unordered_map<T, T> &parent);

    std::vector<T> constructPath(T e, T s, std::unordered_map<T, std::unordered_map<T, T>> &parent);

    void BFS01(T s);

    void kBFS_DialsAlgo(T s, int maxWeight);

    void floydWarshall();
};

#include "GraphImplementation.h"

#endif