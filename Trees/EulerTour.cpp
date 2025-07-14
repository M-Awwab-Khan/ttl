#include <bits/stdc++.h>
using namespace std;

// Segment Tree implementation
struct Tree {
	typedef long long T;
	static constexpr T unit = 0;
	T f(T a, T b) { return a + b; } // (any associative fn)
	vector<T> s; int n;
	Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
	void update(int pos, T val) {
		for (s[pos += n] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};

vector<vector<int>> neighbors;
vector<int> start;
vector<int> e;
int timer = 1;

void euler_tour(int at, int prev) {
	start[at] = timer++;
	for (int n : neighbors[at]) {
		if (n != prev) { euler_tour(n, at); }
	}
	e[at] = timer - 1;
}


int main() {
    int n, q; cin >> n >> q;
    vector<int> values(n + 1);
    neighbors.resize(n + 1);
    start.resize(n + 1);
    e.resize(n + 1);

    for (int i = 1; i <= n; ++i) {
        cin >> values[i];
    }

    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        neighbors[u].push_back(v);
        neighbors[v].push_back(u);
    }
    euler_tour(1, 0);
    Tree seg_tree(n + 1); // Changed from n to n+1
    for (int i = 1; i <= n; ++i) {
        seg_tree.update(start[i], values[i]);
    }

    while (q--) {
        int type, u, v; cin >> type;
        if (type == 1) { // Update
            cin >> u >> v;
            seg_tree.update(start[u], v);
        } else { // Query
            cin >> u;
            cout << seg_tree.query(start[u], e[u] + 1) << endl;
        }
    }
    return 0;
}
