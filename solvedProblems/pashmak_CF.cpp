#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
#define sz(x) ((int)(x).size())
struct FT {
	vector<ll> s;
	FT(int n) : s(n) {}
	void update(int pos, ll dif) { // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
	}
	ll query(int pos) { // sum of values in [0, pos)
		ll res = 0;
		for (; pos > 0; pos &= pos - 1) res += s[pos-1];
		return res;
	}
	int lower_bound(ll sum) {// min pos st sum of [0, pos] >= sum
		// Returns n if no sum is >= sum, or -1 if empty sum is.
		if (sum <= 0) return -1;
		int pos = 0;
		for (int pw = 1 << 25; pw; pw >>= 1) {
			if (pos + pw <= sz(s) && s[pos + pw-1] < sum)
				pos += pw, sum -= s[pos-1];
		}
		return pos;
	}
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin >> n;

    unordered_map<int, int> mp1;
    vector<int> aa(n);
    vector<int> a(n); for (int i = 0; i < n; ++i) {
        cin >> a[i];
        mp1[a[i]]++;
        aa[i] = mp1[a[i]];
    }

    unordered_map<int, int> mp2;
    vector<int> bb(n);
    for (int i = n-1; i >= 0; --i) {
        mp2[a[i]]++;
        bb[i] = mp2[a[i]];
    }


    FT ft(n + 1);
    long long ans = 0;
    for (int i = n-1; i>= 0; --i) {
        ans += ft.query(aa[i]);
        ft.update(bb[i], 1);
    }
    cout << ans << "\n";
    return 0;
}