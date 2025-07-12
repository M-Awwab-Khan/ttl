#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
const int inf = 1e9;
struct Node {
	Node *l = 0, *r = 0;
	int lo, hi, mset = inf, madd = 0, val = -inf;
	Node(int lo,int hi):lo(lo),hi(hi){} // Large interval of -inf
	Node(vi& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			val = max(l->val, r->val);
		}
		else val = v[lo];
	}
	int query(int L, int R) {
		if (R <= lo || hi <= L) return -inf;
		if (L <= lo && hi <= R) return val;
		push();
		return max(l->query(L, R), r->query(L, R));
	}
	void set(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) mset = val = x, madd = 0;
		else {
			push(), l->set(L, R, x), r->set(L, R, x);
			val = max(l->val, r->val);
		}
	}
	void add(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			if (mset != inf) mset += x;
			else madd += x;
			val += x;
		}
		else {
			push(), l->add(L, R, x), r->add(L, R, x);
			val = max(l->val, r->val);
		}
	}
	void push() {
		if (!l) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
		}
		if (mset != inf)
			l->set(lo,hi,mset), r->set(lo,hi,mset), mset = inf;
		else if (madd)
			l->add(lo,hi,madd), r->add(lo,hi,madd), madd = 0;
	}
};

// Example usage and test cases
int main() {
    // Example 1: Build tree from array
    cout << "=== Example 1: Building from array ===" << endl;
    vi arr = {1, 3, 2, 7, 9, 11, 6, 8};
    int n = arr.size();
    Node* tree = new Node(arr, 0, n);
    
    cout << "Initial array: ";
    for(int x : arr) cout << x << " ";
    cout << endl;
    
    // Query maximum in different ranges
    cout << "Max in range [0, 3): " << tree->query(0, 3) << endl; // Should be 3
    cout << "Max in range [3, 6): " << tree->query(3, 6) << endl; // Should be 11
    cout << "Max in range [0, 8): " << tree->query(0, 8) << endl; // Should be 11
    
    cout << "\n=== Example 2: Range updates ===" << endl;
    
    // Range set operation
    cout << "Setting range [1, 4) to value 5" << endl;
    tree->set(1, 4, 5);
    cout << "Max in range [0, 8): " << tree->query(0, 8) << endl; // Should be 11
    cout << "Max in range [1, 4): " << tree->query(1, 4) << endl; // Should be 5
    
    // Range add operation
    cout << "Adding 3 to range [2, 6)" << endl;
    tree->add(2, 6, 3);
    cout << "Max in range [2, 6): " << tree->query(2, 6) << endl; // Should be 14 (11+3)
    cout << "Max in range [0, 2): " << tree->query(0, 2) << endl; // Should be 5
    
    cout << "\n=== Example 3: Dynamic tree (starts empty) ===" << endl;
    
    // Create empty tree for large range
    Node* dynamicTree = new Node(0, 1000000);
    
    cout << "Initial max in [0, 10): " << dynamicTree->query(0, 10) << endl; // Should be -inf
    
    // Set some ranges
    dynamicTree->set(5, 8, 100);
    dynamicTree->set(15, 20, 50);
    
    cout << "After setting [5, 8) to 100 and [15, 20) to 50:" << endl;
    cout << "Max in [0, 10): " << dynamicTree->query(0, 10) << endl; // Should be 100
    cout << "Max in [10, 25): " << dynamicTree->query(10, 25) << endl; // Should be 50
    cout << "Max in [0, 25): " << dynamicTree->query(0, 25) << endl; // Should be 100
    
    // Add to overlapping range
    dynamicTree->add(3, 12, 25);
    cout << "After adding 25 to range [3, 12):" << endl;
    cout << "Max in [5, 8): " << dynamicTree->query(5, 8) << endl; // Should be 125
    cout << "Max in [8, 12): " << dynamicTree->query(8, 12) << endl; // Should be 25
    
    cout << "\n=== Example 4: Competitive programming scenario ===" << endl;
    
    // Simulate a problem where we need range max queries and updates
    vi scores = {10, 20, 15, 30, 25, 40, 35, 50};
    Node* scoreTree = new Node(scores, 0, scores.size());
    
    cout << "Initial scores: ";
    for(int x : scores) cout << x << " ";
    cout << endl;
    
    // Query operations
    cout << "Best score in first half [0, 4): " << scoreTree->query(0, 4) << endl;
    cout << "Best score in second half [4, 8): " << scoreTree->query(4, 8) << endl;
    
    // Bonus points for range of players
    cout << "Giving +10 bonus to players [2, 6)" << endl;
    scoreTree->add(2, 6, 10);
    
    cout << "New best score in [2, 6): " << scoreTree->query(2, 6) << endl; // Should be 50
    cout << "Overall best score: " << scoreTree->query(0, 8) << endl; // Should be 60
    
    // Reset some players' scores
    cout << "Resetting players [1, 3) to score 100" << endl;
    scoreTree->set(1, 3, 100);
    
    cout << "Best score in [0, 4): " << scoreTree->query(0, 4) << endl; // Should be 100
    cout << "Overall best score: " << scoreTree->query(0, 8) << endl; // Should be 100
    
    return 0;
}