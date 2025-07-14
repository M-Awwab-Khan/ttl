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
vector<vi> adjMat;

bool bfs(vi &parent)
{
    fill(all(parent), -1);
    parent[1] = -2;
    queue<int> q;

    q.push(1);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        f(v, 1, n + 1)
        {
            if (adjMat[u][v] && parent[v] == -1)
            {
                parent[v] = u;
                q.push(v);

                if (v == n)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

void solve()
{
    cin >> n >> m;
    adjMat.resize(n + 1, vi(n + 1, 0));

    int a, b;
    f(i, 0, m)
    {
        cin >> a >> b;
        adjMat[a][b] = 1;
        adjMat[b][a] = 0;
    }

    vector<vi> res;

    vi parent(n + 1, -1);

    int days = 0;
    while (bfs(parent))
    {
        days++;
        vi path;
        int e = n, s = 1;
        for (int u = e; u != s; u = parent[u])
        {
            adjMat[parent[u]][u]--;
            adjMat[u][parent[u]]++;
            path.pb(u);
        }
        path.pb(s);
        reverse(all(path));
        res.pb(path);
    }

    cout << res.size() << '\n';
    for (vi p : res)
    {
        cout << p.size() << '\n';
        print_v(p);
        cout << '\n';
    }
}

// Problem Link: https://cses.fi/problemset/task/1711

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