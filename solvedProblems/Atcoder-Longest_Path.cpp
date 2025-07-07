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
int n, m, u, v;
vector<vi> edges;
vi vis;
vector<vi> adj;

int ans = 0;

int dfs(int u)
{

    // ans = max(ans, depth);
    int count = 0;
    for (int eId : adj[u])
    {
        if (vis[eId] == 0)
        {
            vis[eId] = 1;
            edges[eId][2] = max(edges[eId][2], 1 + dfs(edges[eId][1]));
        }
        count = max(count, edges[eId][2]);
    }

    ans = max(ans, count);
    return count;
}

void solve()
{
    cin >> n >> m;
    edges.resize(m);
    vis.resize(m, 0);
    adj.resize(n + 1);
    f(i, 0, m)
    {
        cin >> u >> v;
        edges[i] = {u, v, 0};
        adj[u].pb(i);
    }

    // cout << "CORR\n";
    // return;

    f(i, 0, m)
    {
        if (vis[i] == 0)
        {
            dfs(edges[i][0]);
        }
    }

    cout << ans << '\n';
}

// Problem Link: https://atcoder.jp/contests/dp/tasks/dp_g?lang=en

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