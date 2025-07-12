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

// Example usage of Fenwick Tree
int main() {
	// Create a Fenwick Tree for array of size 10
	FT ft(10);
	
	// Example 1: Basic updates and queries
	cout << "=== Basic Usage ===" << endl;
	
	// Update positions with values
	ft.update(0, 5);   // a[0] += 5
	ft.update(1, 3);   // a[1] += 3
	ft.update(2, 7);   // a[2] += 7
	ft.update(5, 2);   // a[5] += 2
	
	// Query prefix sums
	cout << "Sum [0, 3): " << ft.query(3) << endl;  // 5 + 3 + 7 = 15
	cout << "Sum [0, 6): " << ft.query(6) << endl;  // 5 + 3 + 7 + 0 + 0 + 2 = 17
	cout << "Sum [0, 1): " << ft.query(1) << endl;  // 5
	
	// Example 2: Range sum queries
	cout << "\n=== Range Sum Queries ===" << endl;
	// To get sum in range [l, r), use query(r) - query(l)
	int l = 1, r = 4;
	ll range_sum = ft.query(r) - ft.query(l);
	cout << "Sum [" << l << ", " << r << "): " << range_sum << endl;  // 3 + 7 = 10
	
	// Example 3: Lower bound functionality
	cout << "\n=== Lower Bound Usage ===" << endl;
	cout << "First position where prefix sum >= 8: " << ft.lower_bound(8) << endl;   // Should be 2
	cout << "First position where prefix sum >= 15: " << ft.lower_bound(15) << endl; // Should be 3
	cout << "First position where prefix sum >= 20: " << ft.lower_bound(20) << endl; // Should be 6
	
	// Example 4: Frequency counting and k-th element
	cout << "\n=== Frequency Counting ===" << endl;
	FT freq(100);  // For values 0-99
	
	// Add some elements
	freq.update(10, 1);  // Add element 10
	freq.update(20, 1);  // Add element 20
	freq.update(30, 1);  // Add element 30
	freq.update(20, 1);  // Add another element 20
	
	cout << "Total elements: " << freq.query(100) << endl;  // 4 elements
	cout << "Elements <= 25: " << freq.query(26) << endl;   // 3 elements (10, 20, 20)
	
	// Find k-th smallest element (1-indexed)
	int k = 2;
	int kth_element = freq.lower_bound(k);
	cout << k << "-th smallest element is at position: " << kth_element << endl;  // Should be 20
    return 0;
}