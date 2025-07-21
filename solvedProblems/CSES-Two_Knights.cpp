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

ll nC2(ll n)
{
    return (n * (n - 1)) / 2;
}

vll res(1e4 + 5, 0);

void solve()
{
    res[2] = 6;
    res[3] = 28;
    res[4] = 96;

    ll n;
    ll totalSquares;
    cin >> n;

    f(k, 1, n + 1)
    {
        if (k > 4)
        {
            totalSquares = k * k;
            // Will only compute the added layer and then add the previously calculated layer.
            res[k] = res[k - 1];

            // Both Nights Placed on Corners.
            res[k] += nC2(3);

            // One Knight Placed on a Corner.
            res[k] += 3 * (totalSquares - 5);

            // Both Knights are placed on corner-adjacent square.
            res[k] += nC2(4);

            // One Knight placed on corner-adjacent square.
            res[k] += 4 * (totalSquares - 10);

            // Both Knight placed on remaing squares.
            res[k] += nC2(2 * (k - 4));

            // One Knight placed on remaining squares.

            res[k] += (2 * (k - 4)) * (totalSquares - 4 - (k + k - 1));

            res[k] += 2;
            // When We place knight at (k, k - 2), We attack (k-1, k)
            // When We place knight at (k - 2, k), We attack (k, k - 1)
            // Thus (k - 1, k) and (k, k - 1) are removed 2 times.
        }

        cout << res[k] << '\n';
    }
}

// Problem Link: https://cses.fi/problemset/task/1072

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