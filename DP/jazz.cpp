#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int len = 1; len <= n; ++len) {
        for (int l = 0; l + len - 1 < n; ++l) {
            int r = l + len - 1;
            if (l == r) {
                dp[l][r] = 1; // single character, need to delete it
            } else if (s[l] == s[r]) {
                dp[l][r] = dp[l+1][r-1];
            } else {
                dp[l][r] = min(dp[l+1][r], dp[l][r-1]) + 1;
            }

            // Try all midpoints for partition
            for (int k = l; k < r; ++k) {
                dp[l][r] = min(dp[l][r], dp[l][k] + dp[k+1][r]);
            }
        }
    }

    cout << dp[0][n-1] << '\n';
    return 0;
}