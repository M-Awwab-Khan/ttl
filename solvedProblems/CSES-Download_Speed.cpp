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

int n, m;
vector<vector<pii>> g;

ll BFS(int s, int t, vector<vector<pii>> &adjList, vector<int> &parent, vector<vector<ll>> &capacity)
{
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<ll, ll>> q;
    q.push({s, LONG_LONG_MAX});

    while (!q.empty())
    {
        auto [u, flow] = q.front();
        q.pop();

        for (auto [v, w] : adjList[u])
        {
            if (parent[v] == -1 && capacity[u][v])
            {
                parent[v] = u;
                // cout << u << ' ' << v << ' ' << min(flow, capacity[u][v]) << '\n';
                ll newFlow = min(flow, capacity[u][v]);
                if (v == t)
                {
                    return newFlow;
                }

                q.push({v, newFlow});
            }
        }
    }

    return 0;
}

void solve()
{
    cin >> n >> m;
    g.resize(n + 1);

    vector<vector<ll>> capacity(n + 1, vll(n + 1, 0));

    ll u, v, w;
    f(i, 0, m)
    {
        cin >> u >> v >> w;
        g[u].pb({v, w});
        g[v].pb({u, 0});
        capacity[u][v] += w;
        capacity[v][u] += 0;
    }

    // Edmons Karp
    ll flow = 0;
    ll newFlow = 0;
    vi parent(n + 1, -1);
    while (newFlow = BFS(1, n, g, parent, capacity))
    {
        // cout << "New Flow: " << newFlow << '\n';
        flow += newFlow;
        ll curr = n;
        while (curr != 1)
        {
            ll prev = parent[curr];
            capacity[prev][curr] -= newFlow;
            capacity[curr][prev] += newFlow;
            curr = prev;
        }
    }

    cout << flow << '\n';
}

// Problem Link: https://cses.fi/problemset/task/1694

int main()
{
    ios::ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}