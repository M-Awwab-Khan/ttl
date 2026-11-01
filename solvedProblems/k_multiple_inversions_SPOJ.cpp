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

    long long n, k; cin >>n >> k;

    vector<long long> a(n);
    vector<long long> modified;
    vector<long long> b(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        modified.push_back(a[i]);
        modified.push_back(a[i]*k);
        b[i] = a[i]*k;
    }
    sort(modified.begin(), modified.end());
    unique(modified.begin(), modified.end());

    vector<int> ar(n);
    vector<int> br(n);
    for (int i = 0; i < n; ++i) {
        ar[i] = lower_bound(modified.begin(), modified.end(), a[i]) - modified.begin() + 1;
        br[i] = lower_bound(modified.begin(), modified.end(), b[i]) - modified.begin() + 1;
    }

    FT ft(modified.size() + 10);
    ll ans = 0;
    for (int i = n-1; i >= 0; --i) {
        ans += ft.query(ar[i]); 
        ft.update(br[i], 1);
    }
    cout << ans << "\n";
}