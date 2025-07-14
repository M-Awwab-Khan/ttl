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

int n, m, k, orgN;
vector<vi> adjList;
vi match;
vector<bool> used;

bool tryKuhn(int u)
{
    if (used[u])
    {
        return false;
    }
    used[u] = true;

    for (int v : adjList[u])
    {
        if (match[v] == -1 || tryKuhn(match[v]))
        {
            match[v] = u;
            return true;
        }
    }
    return false;
}

void solve()
{
    cin >> orgN >> m >> k;
    n = orgN + m;
    adjList.resize(n + 1);
    match.resize(n + 1, -1);

    int a, b;
    f(i, 0, k)
    {
        cin >> a >> b;
        b += orgN;
        // cout << a << ' ' << b << ' ' << adjList.size() << '\n';
        adjList[a].pb(b);
        adjList[b].pb(a);
    }
    // cout << "Corr\n";
    // return;

    vector<bool> used1(n + 1, false);
    used.resize(n + 1, false);

    f(u, 1, n + 1)
    {
        for (int v : adjList[u])
        {
            if (match[v] == -1)
            {
                match[v] = u;
                used1[u] = true;
                break;
            }
        }
    }

    f(v, 1, n + 1)
    {
        if (used1[v])
        {
            continue;
        }
        used.assign(n + 1, false);
        tryKuhn(v);
    }

    cout << (n + 1 - count(all(match), -1)) / 2 << '\n';
    f(i, 1, orgN + 1)
    {
        if (match[i] != -1)
        {
            cout << i << ' ' << match[i] - orgN << '\n';
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