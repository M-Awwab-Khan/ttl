#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = a; i < b; ++i)
#define sz(x) ((int)(x).size())
template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j,0,sz(jmp[k]))
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

// example usage
int main() {
    vector<int> V = {1, 3, 2, 7, 9, 5};
    RMQ<int> rmq(V);
    cout << "Minimum between indices 1 and 4: " << rmq.query(1, 4) << endl; // Output: 2
    cout << "Minimum between indices 0 and 5: " << rmq.query(0, 6) << endl; // Output: 1
    return 0;
}