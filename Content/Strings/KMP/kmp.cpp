#include "bits/stdc++.h"

using namespace std;

void kmpAutomation(int n, string& p) {
    int m = p.size();
 
    // Step 1: Compute KMP pi array
    vector<int> pi(m);
    for (int i = 1; i < m; i++) {
        int j = pi[i - 1];
        while (j > 0 && p[i] != p[j])
            j = pi[j - 1];
        if (p[i] == p[j])
            j++;
        pi[i] = j;
    }
 
    // Step 2: Build String Automaton
    vector<vector<int>> aut(m, vector<int>(26));
    for (int j = 0; j < m; j++) {
        for (int c = 0; c < 26; c++) {
            if (j > 0 && 'A' + c != p[j])
                aut[j][c] = aut[pi[j - 1]][c];
            else
                aut[j][c] = j + ('A' + c == p[j]);
        }
    }
 
    // Step 3: DP Table
    // dp[i][j] = ways to build a string of length i ending in automaton state j
    vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, 0));
    dp[0][0] = 1;
 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= m; j++) {
            if (dp[i][j] == 0) continue;
            
            if (j == m) {
                // Absorbing state: once matched, any character keeps it matched
                dp[i + 1][m] = (dp[i + 1][m] + dp[i][m] * 26LL) % MOD;
            } else {
                // Transition to next state for all 26 characters
                for (int c = 0; c < 26; c++) {
                    int nxt = aut[j][c];
                    dp[i + 1][nxt] = (dp[i + 1][nxt] + dp[i][j]) % MOD;
                }
            }
        }
    }
 
    cout << dp[n][m] << "\n";
}