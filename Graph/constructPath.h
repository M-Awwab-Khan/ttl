#pragma once

#include "Graph.h"
#include <algorithm>

template <typename T>
std::vector<T> Graph<T>::constructPath(T e, T s, std::unordered_map<T, T> &parent)
{
    std::vector<T> result;
    for (T u = e; u != s; u = parent[u])
    {
        result.push_back(u);
    }
    result.push_back(s);
    std::reverse(result.begin(), result.end());
    return result;
}

template <typename T>
std::vector<T> Graph<T>::constructPath(T e, T s, std::unordered_map<T, std::unordered_map<T, T>> &parent)
{
    std::cout << s << " -> " << e << '\n';
    std::vector<T> result;
    for (T u = e; u != s; u = parent[s][u])
    {
        result.push_back(u);
    }
    result.push_back(s);
    std::reverse(result.begin(), result.end());
    return result;
}