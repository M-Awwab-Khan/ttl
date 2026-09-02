
#include "bits/stdc++.h"

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

using namespace std;

template <class T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define ll long long
#define vll vector<ll>
#define vi vector<int>
#define vvi vector<vi>
#define vvll vector<vll>
#define endl '\n'
#define pb push_back

#define f(i, s, e) for (ll i = (s); i < (e); ++i)
#define fr(i, s, e) for (ll i = (s); i > (e); --i)

#define all(a) a.begin(), a.end()

int tc = 1;
void yesno(int x) { cout << (x ? "YES\n" : "NO\n"); }
void printCase(int x)
{
    cout << "Case " << x << ": ";
}

void solve()
{
    ll n;
    cin >> n;
    int k = n;
    f(i, 0, n)
    {
        cout << k++ << ' ';
    }
    cout << endl;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int t = 1;
    cin >> t;
    while (t--)
        solve();

    return 0;
}