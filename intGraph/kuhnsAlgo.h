#include <bits/stdc++.h>
using namespace std;

int n, k;              // n = size of left part, k = size of right part
vector<vector<int>> g; // g[v] = neighbors of v in right part
vector<int> mt;        // mt[to] = matched left node for right node 'to'
vector<bool> used;     // used[v] = visited in DFS

// 🔍 Try to find augmenting path starting from left node v

/*
O(VE)

*/

bool try_kuhn(int v)
{
    if (used[v])
        return false;
    used[v] = true;
    for (int to : g[v])
    {
        if (mt[to] == -1 || try_kuhn(mt[to]))
        {
            mt[to] = v;
            return true;
        }
    }
    return false;
}

int main()
{
    // Sample bipartite graph:
    // Left side: 0, 1, 2
    // Right side: 0, 1, 2
    // Edges: 0-0, 1-0, 1-1, 2-2

    n = 3;
    k = 3;
    g.resize(n);

    g[0].push_back(0);
    g[1].push_back(0);
    g[1].push_back(1);
    g[2].push_back(2);

    mt.assign(k, -1); // All unmatched on right side

    // ✅ Greedy initial matching
    vector<bool> used1(n, false);
    for (int v = 0; v < n; ++v)
    {
        for (int to : g[v])
        {
            if (mt[to] == -1)
            {
                mt[to] = v;
                used1[v] = true;
                break;
            }
        }
    }

    // 🔁 Try to improve matching with DFS
    for (int v = 0; v < n; ++v)
    {
        if (used1[v])
            continue;
        used.assign(n, false);
        try_kuhn(v);
    }

    // 📤 Output matching
    cout << "Matched Pairs:\n";
    for (int i = 0; i < k; ++i)
    {
        if (mt[i] != -1)
        {
            cout << "Left " << mt[i] << " <--> Right " << i << '\n';
        }
    }

    return 0;
}