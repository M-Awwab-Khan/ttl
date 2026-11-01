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
    vector<int> a(n); for (int i = 0; i < n ; ++i) cin >> a[i];
    reverse(begin(a), end(a));

    vector<int> rank(a);
    sort(rank.begin(), rank.end());
    unique(rank.begin(), rank.end());

    auto getRank = [&](int x) {
        return lower_bound(rank.begin(), rank.end(), x) - rank.begin() + 1;
    };

    FT ft(n + 1);
    ll ans = 0;
    vector<int> pairs(n);
    for (int i = 0; i < n; ++i) {
        int r = getRank(a[i]);
        pairs[i] = ft.query(r);
        ft.update(r, 1);
    }

    FT ft2(n + 1);
    for (int i = 0; i < n; ++i) {
        int r = getRank(a[i]);
        ans += ft2.query(r);
        ft2.update(r, pairs[i]);
    }
    cout << ans << "\n";
}