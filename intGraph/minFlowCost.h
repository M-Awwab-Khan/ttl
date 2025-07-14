#include <bits/stdc++.h>
using namespace std;

// 🧱 Edge structure
struct Edge
{
    int from, to, capacity, cost;
};

// Graph
vector<vector<int>> adj;
vector<vector<int>> capacity, cost;
const int INF = 1e9;

// 🔍 Dijkstra with Potentials
void dijkstra(int N, int s, vector<int> &dist, vector<int> &parent, vector<int> &pot)
{
    dist.assign(N, INF);
    parent.assign(N, -1);
    dist[s] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, s});

    while (!pq.empty())
    {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u])
            continue;

        for (int v : adj[u])
        {
            if (capacity[u][v] > 0)
            {
                int weight = cost[u][v] + pot[u] - pot[v]; // Reduced cost
                if (dist[v] > dist[u] + weight)
                {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
    }
}

// 🚰 Min-Cost Flow using Dijkstra + Potentials
int min_cost_flow(int N, vector<Edge> edges, int K, int s, int t)
{
    adj.assign(N, vector<int>());
    cost.assign(N, vector<int>(N, 0));
    capacity.assign(N, vector<int>(N, 0));

    for (Edge e : edges)
    {
        adj[e.from].push_back(e.to);
        adj[e.to].push_back(e.from);
        cost[e.from][e.to] = e.cost;
        cost[e.to][e.from] = -e.cost;
        capacity[e.from][e.to] = e.capacity;
    }

    vector<int> dist, parent, pot(N, 0);
    int flow = 0, total_cost = 0;

    while (flow < K)
    {
        dijkstra(N, s, dist, parent, pot);

        if (dist[t] == INF)
            break;

        // Update potentials
        for (int i = 0; i < N; i++)
        {
            if (dist[i] < INF)
                pot[i] += dist[i];
        }

        // Find bottleneck
        int f = K - flow;
        for (int cur = t; cur != s; cur = parent[cur])
        {
            f = min(f, capacity[parent[cur]][cur]);
        }

        // Push flow
        flow += f;
        total_cost += f * pot[t]; // cost = dist[t] + pot[t] - pot[s] == pot[t]
        for (int cur = t; cur != s; cur = parent[cur])
        {
            int prev = parent[cur];
            capacity[prev][cur] -= f;
            capacity[cur][prev] += f;
        }
    }

    if (flow < K)
        return -1;
    return total_cost;
}
