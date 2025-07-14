#include <bits/stdc++.h>
using namespace std;

/* TYPES  */
#define ll long long
#define pii pair<int, int>
#define pll pair<long long, long long>
#define vi vector<int>
#define vll vector<long long>
#define mii map<int, int>
#define si set<int>
#define sc set<char>

/* FUNCTIONS */
#define f(i, s, e) for (long long int i = s; i < e; i++)
#define fe(i, s, e) for (long long int i = s; i <= e; i++)
#define fr(i, e, s) for (long long int i = e - 1; i >= s; i--)
#define pb push_back
#define eb emplace_back
#define all(x) x.begin(), x.end()

/* PRINTS */
template <class T>
void print_v(vector<T> &v)
{
    for (auto x : v)
        cout << x << ' ';
}

/* UTILS */
#define MOD 1000000007
#define PI 3.1415926535897932384626433832795
#define read(type) readInt<type>()
ll min(ll a, int b)
{
    if (a < b)
        return a;
    return b;
}
ll min(int a, ll b)
{
    if (a < b)
        return a;
    return b;
}
ll max(ll a, int b)
{
    if (a > b)
        return a;
    return b;
}
ll max(int a, ll b)
{
    if (a > b)
        return a;
    return b;
}
ll gcd(ll a, ll b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }
bool prime(ll a)
{
    if (a == 1)
        return 0;
    for (int i = 2; i <= round(sqrt(a)); ++i)
        if (a % i == 0)
            return 0;
    return 1;
}
void yes() { cout << "YES\n"; }
void no() { cout << "NO\n"; }
void printCase(int i) { cout << "Case " << i << ": "; }

struct Edge
{
    int v, rev;
    long long cap, flow, low;
};

vector<vector<Edge>> adjList(205);
vll demand(205);
int n, m;
int s = 201;
int t = 202;
vector<pii> orgEdges;

void addEdge(int u, int v, ll l, ll c, bool org = false)
{
    demand[u] -= l;
    demand[v] += l;

    Edge a = {v, (int)adjList[v].size(), c - l, 0, l};
    Edge b = {u, (int)adjList[u].size(), 0, 0, l};
    adjList[u].push_back(a);
    adjList[v].push_back(b);

    if (org)
    {

        orgEdges.pb({u, adjList[u].size() - 1});
    }
}

bool bfs(vector<int> &level)
{
    fill(level.begin(), level.end(), -1);
    queue<int> q;
    q.push(s);
    level[s] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (Edge &e : adjList[u])
        {
            if (level[e.v] == -1 && e.cap - e.flow > 0)
            {
                level[e.v] = level[u] + 1;
                q.push(e.v);
            }
        }
    }
    return level[t] != -1;
}

long long dfs(int u, long long pushed, vector<int> &ptr, vector<int> &level)
{
    if (pushed == 0 || u == t)
        return pushed;
    for (int &cid = ptr[u]; cid < (int)adjList[u].size(); ++cid)
    {
        Edge &e = adjList[u][cid];
        if (level[e.v] == level[u] + 1 && e.cap - e.flow > 0)
        {
            long long tr = dfs(e.v, min(pushed, e.cap - e.flow), ptr, level);
            if (tr == 0)
                continue;
            e.flow += tr;
            adjList[e.v][e.rev].flow -= tr;
            return tr;
        }
    }
    return 0;
}

ll maxFlow()
{
    long long flow = 0;
    vector<int> level(205);
    while (bfs(level))
    {
        vector<int> ptr(205, 0);
        while (long long pushed = dfs(s, INT_MAX, ptr, level))
        {
            flow += pushed;
        }
    }
    return flow;
}

void solve()
{
    cin >> n >> m;
    int u, v;
    ll l, c;
    f(i, 0, m)
    {
        cin >> u >> v >> l >> c;
        addEdge(u, v, l, c, true);
    }

    addEdge(t, s, 0, INT_MAX);
    // All Edges, Done

    long long totalDemand = 0;
    f(i, 1, n + 1)
    {
        if (demand[i] > 0)
        {
            addEdge(s, i, 0, demand[i]);
            totalDemand += demand[i];
        }
        else if (demand[i] < 0)
        {
            addEdge(i, t, 0, -demand[i]);
        }
    }

    long long flow = maxFlow();
    if (flow == totalDemand)
    {
        yes();
        for (auto [i, j] : orgEdges)
        {
            Edge e = adjList[i][j];
            cout << e.flow + e.low << '\n';
        }
    }
    else
    {
        no();
    }
}

// Problem Link: https://vjudge.net/problem/Gym-100199B

int main()
{
    ios::ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int t = 1;
    freopen("cooling.in", "r", stdin);
    freopen("cooling.out", "w", stdout);
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}