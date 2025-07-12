#include <bits/stdc++.h>
using namespace std;

string num;
long long int dp[20][200][2];

// Digit DP function
long long int solve(int pos, long long int sum, bool tight) {
    if (pos == num.size()) {
        return sum;
    }

    if (dp[pos][sum][tight] != -1) return dp[pos][sum][tight];

    int limit = tight ? num[pos] - '0' : 9;
    long long int res = 0;

    for (int dig = 0; dig <= limit; ++dig) {
        bool new_tight = tight && (dig == limit);
        long long int new_sum = sum + dig;
        res += solve(pos + 1, new_sum, new_tight);
    }

    return dp[pos][sum][tight] = res;
}

long long int calculate_sum(string n) {
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
    int t; cin >> t;
    while (t--) {

        string a, b; cin >> a >> b;
    
        string a_minus_1 = a == "0" ? "0" : decrement(a);
    
        long long int result = calculate_sum(b) - calculate_sum(a_minus_1);
        cout << result << '\n';
    }
}
