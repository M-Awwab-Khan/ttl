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

vector<int> adj[100005];
long long dp[100005][2];
void dfs(int node, int parent) {

    dp[node][0] = 1; 
    dp[node][1] = 1; 

    for (int child : adj[node]) {
        if (child == parent) continue; // avoid going back to parent
        dfs(child, node);
        dp[node][0] = (dp[node][0] * (dp[child][0] + dp[child][1]) % MOD) % MOD; // not taking this node, can take or not take child
        dp[node][1] = (dp[node][1] * dp[child][0]) % MOD; // taking this node, can only not take child
    }
}
void solve() {
    int n; cin >> n;
    f(i, 0, n-1) {
        int u, v; cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dfs(1, -1); // assuming 1 is the root and has no parent
    cout << (dp[1][0] + dp[1][1]) % MOD << endl;;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    // int t; cin >> t; while(t--)
    solve();
    return 0;
}