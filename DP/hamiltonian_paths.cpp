#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
#define ll long long
#define vi vector<int>
#define vll vector<ll>
#define all(a) a.begin(), a.end()
#define f(i, s, e) for (ll i = s; i < e; ++i)
#define fr(i, s, e) for (ll i = s; i > e; --i)
#define vvi vector<vector<int>>
#define pb push_back
template <class T> void print_v(vector<T> &v) {for (auto x : v) cout << x << ' '; cout << '\n'; }
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fraction(a) cout.unsetf(ios::floatfield); cout.precision(a); cout.setf(ios::fixed,ios::floatfield);
void yes() { cout<<"YES\n"; }
void no() { cout<<"NO\n"; }

const int MOD = 1e9 + 7;

const int MAXN = 20;
void solve() {
    int n, m; cin >> n >> m;
    vvi adj(n+1, vi());

    f(i, 0, m) {
        int s, e; cin >> s >> e; --s; --e;
        adj[s].pb(e);
    }

    int N = 1 << n;
    vvi dp(N, vi(n, 0));

    dp[1 << 0][0] = 1; // first node alr visited
    // loop on all masks

    for (int mask = 1; mask < N; ++mask) {
        // loop on all nodes
        for (int u = 0; u < n; ++u) {
            if (!((1 << u) & mask)) continue;  // if u is not visited in this mask
            if (dp[mask][u] == 0) continue; // no path ends here with this mask
            for (int v : adj[u]) {
                if (((1 << v) & mask)) continue; // same v is visited, so skip
                int nextMask = mask | (1 << v);
                dp[nextMask][v] = (dp[nextMask][v] + dp[mask][u]) % MOD;
            }
        }
    }
    cout << dp[(1<<n) -1][n-1] << endl;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    // int t; cin >> t; while(t--)
    solve();
    return 0;
}