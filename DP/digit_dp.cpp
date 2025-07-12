#include <bits/stdc++.h>
using namespace std;

string num;
int dp[20][20][2];
int K, D;

// Digit DP function
int solve(int pos, int cnt, bool tight) {
    if (pos == num.size()) {
        return cnt == K;
    }

    if (dp[pos][cnt][tight] != -1) return dp[pos][cnt][tight];

    int limit = tight ? num[pos] - '0' : 9;
    int res = 0;

    for (int dig = 0; dig <= limit; ++dig) {
        bool new_tight = tight && (dig == limit);
        int new_cnt = cnt + (dig == D);
        res += solve(pos + 1, new_cnt, new_tight);
    }

    return dp[pos][cnt][tight] = res;
}

// Count how many numbers ≤ n have exactly k d's
int count_with_k_d(string n) {
    num = n;
    memset(dp, -1, sizeof(dp));
    return solve(0, 0, true);
}

// Utility to decrement a number string (to get n - 1)
string decrement(string s) {
    for (int i = s.size() - 1; i >= 0; --i) {
        if (s[i] > '0') {
            s[i]--;
            break;
        } else {
            s[i] = '9';
        }
    }
    if (s[0] == '0') s = s.substr(1); // remove leading zero
    return s;
}

int main() {
    string n, m;
    int k, d;
    cin >> n >> m >> k >> d;

    K = k;
    D = d;

    string n_minus_1 = decrement(n);

    int result = count_with_k_d(m) - count_with_k_d(n_minus_1);
    cout << result << '\n';
}
