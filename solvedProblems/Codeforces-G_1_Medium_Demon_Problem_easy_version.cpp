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

void getCycleNodes(int u, vi &adj, vi &visited, vi &cycleNodes, vi &parent)
{
    visited[u] = 1;

    if (visited[adj[u]] == 0)
    {
        parent[adj[u]] = u;
        getCycleNodes(adj[u], adj, visited, cycleNodes, parent);
    }
    else if (visited[adj[u]] == 1)
    {
        int v = adj[u];
        int temp = u;
        while (true)
        {
            cycleNodes[temp] = 1;
            if (temp == v)
            {
                break;
            }
            temp = parent[temp];
        }
    }

    visited[u] = 2;
}

int dfsForResult(int u, vector<vi> &backEdges)
{

    int count = 1;
    for (int i : backEdges[u])
    {
        count = max(count, 1 + dfsForResult(i, backEdges));
    }
    return count;
}

void solve()
{
    int n;
    cin >> n;
    vi adj(n + 1);
    vector<vi> backEdges(n + 1);
    int v;
    f(i, 1, n + 1)
    {
        cin >> v;
        adj[i] = v;
        backEdges[v].pb(i);
    }

    vi cycleNodes(n + 1, 0);

    vi visited(n + 1, 0);
    vi parent(n + 1, -1);

    f(i, 1, n + 1)
    {
        if (visited[i] == 0)
        {
            getCycleNodes(i, adj, visited, cycleNodes, parent);
        }
    }

    // print_v(cycleNodes);

    int maxCount = 0;
    int count = 0;
    f(i, 1, n + 1)
    {
        // cout << i << ' ' << cycleNodes[i] << ' ' << backEdges[i] << '\n';

        if (cycleNodes[i] == 1)
        {
            for (int v : backEdges[i])
            {
                if (cycleNodes[v] == 0)
                {
                    maxCount = max(maxCount, dfsForResult(v, backEdges));
                }
            }
        }
    }

    cout << maxCount + 2 << '\n';
}

// Problem Link: https://codeforces.com/problemset/problem/2044/G1

int main()
{
    ios::ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}