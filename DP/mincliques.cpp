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

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<bool>> adj(n+1, vector<bool>(n+1, false));

    f(i, 0, m) {
        int s, e; cin >> s >> e;
        --s; --e;
        adj[s][e] = adj[e][s] = true;
    }

    int N = (1 << n);

    // finding all the cliques
    vector<bool> is_clique(N, true);
    vi nodes;
    for (int mask = 0; mask < N; ++mask){
        nodes.clear();
        for (int j = 0; j < n; ++j) {
            if (mask & (1 << j)) nodes.pb(j);
        }
        for (int u = 0; u < nodes.size(); ++u) {
            for (int v = u + 1; v < nodes.size(); ++v) {
                if (!adj[nodes[u]][nodes[v]]) {
                    is_clique[mask] = false;
                }
            }

        }
    }


    //now dp
    vector<int> dp(N, INT_MAX);
    dp[0] = 0;
    for (int mask = 1; mask < N; ++mask) {
        // now iterate on all submasks
        for (int submask = mask; submask; submask = (submask - 1) & mask)  {
            int complement = mask ^ submask;
            if (is_clique[submask]) {
                dp[mask] = min(dp[mask], dp[complement] + 1);
            }
        }
    }

    cout << dp[N - 1] << endl;

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