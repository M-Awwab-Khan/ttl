// 📌 Minimum-Cost Flow using Successive Shortest Paths

#include <bits/stdc++.h>
using namespace std;

// 🧱 Edge structure to hold flow network info
struct Edge
{
    int from, to, capacity, cost;
};

// Implement with Dijkstra for O(N^3)

// 🌐 Graph structure
vector<vector<int>> adj, cost, capacity;
const int INF = 1e9;

// 🔍 SPFA (Shortest Path Faster Algorithm)
void shortest_paths(int n, int source, vector<int> &dist, vector<int> &parent)
{
    dist.assign(n, INF);
    dist[source] = 0;
    vector<bool> in_queue(n, false);
    queue<int> q;
    q.push(source);
    parent.assign(n, -1);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        in_queue[u] = false;
        for (int v : adj[u])
        {
            if (capacity[u][v] > 0 && dist[v] > dist[u] + cost[u][v])
            {
                dist[v] = dist[u] + cost[u][v];
                parent[v] = u;
                if (!in_queue[v])
                {
                    in_queue[v] = true;
                    q.push(v);
                }
            }
        }
    }
}

// 🚰 Min-Cost Flow Algorithm
// Goal: Send exactly K units of flow from s to t, with minimum cost
int min_cost_flow(int N, vector<Edge> edges, int K, int s, int t)
{
    adj.assign(N, vector<int>());
    cost.assign(N, vector<int>(N, 0));
    capacity.assign(N, vector<int>(N, 0));

    // Build the graph
    for (Edge e : edges)
    {
        adj[e.from].push_back(e.to);
        adj[e.to].push_back(e.from); // Add reverse edge
        cost[e.from][e.to] = e.cost;
        cost[e.to][e.from] = -e.cost;
        capacity[e.from][e.to] = e.capacity;
    }

    int flow = 0, total_cost = 0;
    vector<int> dist, parent;

    while (flow < K)
    {
        shortest_paths(N, s, dist, parent);

        // 🚫 No more paths
        if (dist[t] == INF)
            break;

        // 🛠 Find bottleneck (min capacity along path)
        int f = K - flow;
        for (int cur = t; cur != s; cur = parent[cur])
        {
            f = min(f, capacity[parent[cur]][cur]);
        }

        // 🚚 Send flow & update capacities
        flow += f;
        total_cost += f * dist[t];
        for (int cur = t; cur != s; cur = parent[cur])
        {
            capacity[parent[cur]][cur] -= f;
            capacity[cur][parent[cur]] += f;
        }
    }

    // ✅ Check if we reached desired flow
    if (flow < K)
        return -1;
    return total_cost;
}

/*
📘 How it works:
- Build graph with both forward and backward edges
- Repeatedly find cheapest path from s to t (using cost as weight)
- Send as much flow as possible through this path
- Stop when we've sent K units of flow

✅ Result: Minimum total cost to send K flow from s to t
*/
