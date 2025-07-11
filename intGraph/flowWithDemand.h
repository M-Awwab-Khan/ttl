/*

GPT generated, not tested
*/

#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

struct Edge
{
    int v, rev;
    long long cap, flow;
};

class FlowWithDemands
{
public:
    int N;    // Number of nodes in original graph
    int s, t; // Source and Sink in original graph
    int S, T; // Super source and sink
    vector<vector<Edge>> adj;
    vector<long long> demand;

    FlowWithDemands(int n, int source, int sink) : N(n), s(source), t(sink)
    {
        adj.resize(N + 2); // +2 for S and T
        demand.assign(N + 2, 0);
        S = N;     // Super source
        T = N + 1; // Super sink
    }

    void addEdge(int u, int v, long long lower, long long upper)
    {
        // For demand balancing
        demand[u] -= lower;
        demand[v] += lower;

        // Actual edge with capacity = upper - lower
        addInternalEdge(u, v, upper - lower);
    }

    void addInternalEdge(int u, int v, long long cap)
    {
        Edge a = {v, (int)adj[v].size(), cap, 0};
        Edge b = {u, (int)adj[u].size(), 0, 0};
        adj[u].push_back(a);
        adj[v].push_back(b);
    }

    bool bfs(vector<int> &level, vector<vector<Edge>> &graph, int source, int sink)
    {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        q.push(source);
        level[source] = 0;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (Edge &e : graph[u])
            {
                if (level[e.v] == -1 && e.cap - e.flow > 0)
                {
                    level[e.v] = level[u] + 1;
                    q.push(e.v);
                }
            }
        }
        return level[sink] != -1;
    }

    long long dfs(int u, int t, long long pushed, vector<int> &ptr, vector<int> &level, vector<vector<Edge>> &graph)
    {
        if (pushed == 0 || u == t)
            return pushed;
        for (int &cid = ptr[u]; cid < (int)graph[u].size(); ++cid)
        {
            Edge &e = graph[u][cid];
            if (level[e.v] == level[u] + 1 && e.cap - e.flow > 0)
            {
                long long tr = dfs(e.v, t, min(pushed, e.cap - e.flow), ptr, level, graph);
                if (tr == 0)
                    continue;
                e.flow += tr;
                graph[e.v][e.rev].flow -= tr;
                return tr;
            }
        }
        return 0;
    }

    long long maxFlow(vector<vector<Edge>> &graph, int source, int sink)
    {
        long long flow = 0;
        vector<int> level(graph.size());
        while (bfs(level, graph, source, sink))
        {
            vector<int> ptr(graph.size());
            while (long long pushed = dfs(source, sink, INF, ptr, level, graph))
            {
                flow += pushed;
            }
        }
        return flow;
    }

    bool feasibleFlow()
    {
        // Add edge from t to s with INF capacity to allow circulation
        addInternalEdge(t, s, INF);

        long long totalDemand = 0;
        for (int i = 0; i < N; ++i)
        {
            if (demand[i] > 0)
            {
                addInternalEdge(S, i, demand[i]);
                totalDemand += demand[i];
            }
            else if (demand[i] < 0)
            {
                addInternalEdge(i, T, -demand[i]);
            }
        }

        vector<vector<Edge>> tempAdj = adj; // Clone to preserve original
        long long flow = maxFlow(tempAdj, S, T);
        return flow == totalDemand;
    }
};

// Example usage:
int main()
{
    int n = 4; // nodes: 0 (s), 1, 2, 3 (t)
    FlowWithDemands fwd(n, 0, 3);

    // addEdge(u, v, lower_bound, upper_bound)
    fwd.addEdge(0, 1, 3, 7); // edge 0->1 with demand 3, capacity 7
    fwd.addEdge(1, 2, 2, 5);
    fwd.addEdge(2, 3, 2, 5);

    if (fwd.feasibleFlow())
    {
        cout << "A valid flow exists that satisfies all demands.\n";
    }
    else
    {
        cout << "No valid flow that satisfies all demands.\n";
    }

    return 0;
}
