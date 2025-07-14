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

vector<vi> adj((200 * 2) + 7);
vector<vi> cost(405, vi((200 * 2) + 7, 0));
vector<vi> capacity(405, vi((200 * 2) + 7, 0));

vi dist(405, INT_MAX);
vi parent(405, -1);
vi pot(405, 0);

int n;

void dijkstra(int N, int s, vector<int> &dist, vector<int> &parent, vector<int> &pot)
{
    dist.assign(N, INT_MAX);
    parent.assign(N, -1);
    dist[s] = 0;

    // priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    set<pii> pq;
    pq.insert({0, s});

    while (!pq.empty())
    {
        auto [d, u] = *pq.begin();
        pq.erase(pq.begin());
        // if (d != dist[u])
        //     continue;

        for (int v : adj[u])
        {
            if (capacity[u][v] > 0)
            {
                int weight = cost[u][v] + pot[u] - pot[v]; // Reduced cost
                if (dist[v] > dist[u] + weight)
                {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    pq.erase({dist[v], v});
                    pq.insert({dist[v], v});
                }
            }
        }
    }
}

void solve()
{
    cin >> n;
    int c;
    f(u, 1, n + 1)
    {
        f(v, n + 1, n + n + 1)
        {
            cin >> c;
            adj[u].pb(v);
            adj[v].pb(u);
            cost[u][v] = c;
            cost[v][u] = -c;
            capacity[u][v] = 1;
            capacity[v][u] = 0;
        }
    }

    // Source (2n + 1) to Employee
    f(u, 1, n + 1)
    {
        adj[(2 * n) + 1].pb(u);
        capacity[(2 * n) + 1][u] = 1;
    }

    // Sink (2n + 2) to Tasks
    f(u, n + 1, n + n + 1)
    {
        adj[u].pb((2 * n) + 2);
        capacity[u][(2 * n) + 2] = 1;
    }

    int flow = 0;
    int totalCost = 0;

    while (flow < n)
    {
        // cout << "Here\n";
        // return;
        dijkstra(n + n + 3, n + n + 1, dist, parent, pot);

        if (dist[n + n + 2] == INT_MAX)
        {
            break;
        }

        // Update potentials
        for (int i = 1; i < n + n + 3; i++)
        {
            if (dist[i] < INT_MAX)
                pot[i] += dist[i];
        }

        // Find bottleneck
        int f = n - flow;
        for (int cur = n + n + 2; cur != n + n + 1; cur = parent[cur])
        {
            f = min(f, capacity[parent[cur]][cur]);
        }

        // Push flow
        flow += f;
        totalCost += f * pot[n + n + 2]; // cost = dist[t] + pot[t] - pot[s] == pot[t]
        for (int cur = n + n + 2; cur != n + n + 1; cur = parent[cur])
        {
            int prev = parent[cur];
            capacity[prev][cur] -= f;
            capacity[cur][prev] += f;
        }

        // cout << f << '\n';
    }

    cout << totalCost << '\n';

    f(u, 1, n + 1)
    {
        f(v, n + 1, n + n + 1)
        {
            if (capacity[u][v] == 0)
            {
                cout << u << ' ' << v - n << '\n';
            }
        }
    }
}

// Problem Link:

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