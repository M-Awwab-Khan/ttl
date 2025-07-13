#include <bits/stdc++.h>
using namespace std;

// Rolling Hash (Double Hashing) for anagram/substring matching
using ll = long long;
using Hash = pair<ll, ll>;
const ll B1 = 131, B2 = 137;
const ll M1 = 1e9 + 7, M2 = 1e9 + 9;

struct RollingHash {
    vector<ll> h1, h2, p1, p2;
    RollingHash(const string &s) {
        int n = s.size();
        h1 = h2 = p1 = p2 = vector<ll>(n + 1);
        p1[0] = p2[0] = 1;
        for (int i = 0; i < n; ++i) {
            int val = s[i] - 'a' + 1;
            h1[i+1] = (h1[i] * B1 + val) % M1;
            h2[i+1] = (h2[i] * B2 + val) % M2;
            p1[i+1] = (p1[i] * B1) % M1;
            p2[i+1] = (p2[i] * B2) % M2;
        }
    }
    // Hash of substring [l, r)
    Hash get(int l, int r) {
        ll x = (h1[r] - h1[l] * p1[r - l] % M1 + M1) % M1;
        ll y = (h2[r] - h2[l] * p2[r - l] % M2 + M2) % M2;
        return {x, y};
    }
};

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
    RollingHash rh(H);

    // Initialize the first window
    for (int i = 0; i < L; ++i) {
        window[H[i] - 'a']++;
    }

    // Check the first window
    if (window == need) {
        seen.insert(rh.get(0, L));
    }

    // Slide the window
    for (int i = L; i < M; ++i) {
        // Remove the leftmost character from window
        window[H[i - L] - 'a']--;
        // Add the new character to window
        window[H[i] - 'a']++;
        
        // Check if current window is an anagram
        if (window == need) {
            seen.insert(rh.get(i - L + 1, i + 1));
        }
    }

    cout << seen.size() << '\n';
}

