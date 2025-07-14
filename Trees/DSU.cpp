#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define rep(i,a,b) for (int i = (a); i < (b); ++i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()

struct RollbackUF {
	vi e; vector<pii> st;
	RollbackUF(int n) : e(n, -1) {}
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : find(e[x]); }
	int time() { return sz(st); }
	void rollback(int t) {
		for (int i = time(); i --> t;)
			e[st[i].first] = st[i].second;
		st.resize(t);
	}
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		st.push_back({a, e[a]});
		st.push_back({b, e[b]});
		e[a] += e[b]; e[b] = a;
		return true;
	}
};

int main() {
    RollbackUF dsu(5); // 0 to 4

    dsu.join(0, 1);
    int t = dsu.time(); // Save current time (version)
    dsu.join(2, 3);
    dsu.join(1, 2); // Connects 0-1-2-3

    cout << dsu.find(3) << '\n';  // Should print representative of component
    cout << dsu.size(0) << '\n';  // Size of component containing 0

    dsu.rollback(t); // Roll back to state before join(2,3) and join(1,2)
    
    cout << dsu.find(3) << '\n';  // Now 3 is only in its own component
    cout << dsu.size(0) << '\n';  // Only includes 0 and 1

    return 0;
}
