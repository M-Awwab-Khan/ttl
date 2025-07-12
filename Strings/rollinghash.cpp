#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using Hash = pair<ll, ll>;

const ll B1 = 131;
const ll B2 = 137;
const ll MOD1 = 1e9 + 7;
const ll MOD2 = 1e9 + 9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string N, H;
    cin >> N >> H;

    int L = N.size(), M = H.size();
    if (L > M) {
        cout << 0;
        return 0;
    }

    vector<int> need(26, 0), window(26, 0);
    for (char c : N) need[c - 'a']++;

    set<Hash> seen;

    // Compute power for removing leading char
    ll pow1 = 1, pow2 = 1;
    for (int i = 0; i < L - 1; ++i) {
        pow1 = (pow1 * B1) % MOD1;
        pow2 = (pow2 * B2) % MOD2;
    }

    ll h1 = 0, h2 = 0;

    for (int i = 0; i < L; ++i) {
        int val = H[i] - 'a' + 1;
        window[H[i] - 'a']++;
        h1 = (h1 * B1 + val) % MOD1;
        h2 = (h2 * B2 + val) % MOD2;
    }

    if (window == need)
        seen.emplace(h1, h2);

    for (int i = L; i < M; ++i) {
        int out = H[i - L] - 'a' + 1;
        int in = H[i] - 'a' + 1;

        window[H[i - L] - 'a']--;
        window[H[i] - 'a']++;

        // Remove the leading char and add the new char
        h1 = ((h1 - out * pow1 % MOD1 + MOD1) * B1 + in) % MOD1;
        h2 = ((h2 - out * pow2 % MOD2 + MOD2) * B2 + in) % MOD2;

        if (window == need)
            seen.emplace(h1, h2);
    }

    cout << seen.size() << '\n';
}

