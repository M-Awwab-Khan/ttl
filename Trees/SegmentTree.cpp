#include <bits/stdc++.h>
using namespace std;

// Segment Tree implementation
struct Tree {
	typedef int T;
	static constexpr T unit = INT_MIN;
	T f(T a, T b) { return max(a, b); } // (any associative fn)
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


int main() {
    // Example usage
    int n = 10; // Size of the segment tree
    Tree segTree(n);

    // Update values in the segment tree
    for (int i = 0; i < n; ++i) {
        segTree.update(i, i + 1); // Set values from 1 to n
    }

    // Query the maximum value in the range [2, 5)
    cout << "Max in range [2, 5): " << segTree.query(2, 5) << endl; // Should output 5

    // Update a value
    segTree.update(3, 10); // Change value at index 3 to 10

    // Query again
    cout << "Max in range [2, 5) after update: " << segTree.query(2, 5) << endl; // Should output 10

    return 0;
}