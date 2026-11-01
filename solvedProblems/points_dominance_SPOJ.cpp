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


    int t; cin >> t; while(t--) {

        int n, k; cin >> n >> k;
        FT ft(n+1);
        vector<pair<int, int>> points(n); 
        vector<int> ys(n);
        for (int i = 0; i < n; ++i) {
            cin >>points[i].first >> points[i].second;
            ys[i] = points[i].second;
        }
        sort(points.begin(), points.end());
        sort(ys.begin(), ys.end());

        ys.erase(unique(ys.begin(), ys.end()), ys.end());
        
        auto getRank = [&](int y) {
            return lower_bound(ys.begin(), ys.end(), y) - ys.begin() + 1;
        };

        int weird = 0;
        for (int i =0; i < n; ++i) {
            auto [cx, cy] = points[i];

            int ry = getRank(cy);
            long long dominated = ft.query(ry);
            long long notDominated = n - 1 - dominated;
            if (llabs(dominated - notDominated) >= k) ++weird;

            ft.update(ry, 1);
        }
        cout << weird << "\n";
    }
}