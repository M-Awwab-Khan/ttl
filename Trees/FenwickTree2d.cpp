#include "FenwickTree.h"
#include <bits/stdc++.h>
using namespace std;
// using ll = long long;
// using vi = vector<int>;
#define all(x) (x).begin(), (x).end()
// #define sz(x) (int)(x).size()

struct FT2 {
	vector<vi> ys; vector<FT> ft;
	FT2(int limx) : ys(limx) {}
	void fakeUpdate(int x, int y) {
		for (; x < sz(ys); x |= x + 1) ys[x].push_back(y);
	}
	void init() {
		for (vi& v : ys) sort(all(v)), ft.emplace_back(sz(v));
	}
	int ind(int x, int y) {
		return (int)(lower_bound(all(ys[x]), y) - ys[x].begin()); }
	void update(int x, int y, ll dif) {
		for (; x < sz(ys); x |= x + 1)
			ft[x].update(ind(x, y), dif);
	}
	ll query(int x, int y) {
		ll sum = 0;
		for (; x; x &= x - 1)
			sum += ft[x-1].query(ind(x-1, y));
		return sum;
	}
};

int main() {
    // Example usage of 2D Fenwick Tree with coordinate compression
    cout << "=== 2D Fenwick Tree Example ===" << endl;
    
    // Create a 2D Fenwick Tree for a grid with x-coordinates up to 1000
    FT2 ft2d(1001);
    
    // Example points with their coordinates and values
    vector<tuple<int, int, int>> points = {
        {100, 200, 5},   // Point (100, 200) with value 5
        {300, 150, 3},   // Point (300, 150) with value 3
        {100, 400, 7},   // Point (100, 400) with value 7
        {500, 200, 2},   // Point (500, 200) with value 2
        {300, 600, 4},   // Point (300, 600) with value 4
        {700, 300, 6}    // Point (700, 300) with value 6
    };
    
    // Phase 1: Coordinate compression setup
    cout << "\n--- Phase 1: Setting up coordinate compression ---" << endl;
    
    // First, we need to register all y-coordinates for coordinate compression
    for (auto [x, y, val] : points) {
        ft2d.fakeUpdate(x, y);
    }
    
    // Initialize the data structure (sorts y-coordinates and creates 1D trees)
    ft2d.init();
    cout << "Coordinate compression completed." << endl;
    
    // Phase 2: Adding points to the 2D grid
    cout << "\n--- Phase 2: Adding points ---" << endl;
    for (auto [x, y, val] : points) {
        ft2d.update(x, y, val);
        cout << "Added point (" << x << ", " << y << ") with value " << val << endl;
    }
    
    // Phase 3: Range sum queries
    cout << "\n--- Phase 3: Range Sum Queries ---" << endl;
    
    // Query sum in rectangle from (0,0) to (x,y) exclusive
    vector<pair<int, int>> query_points = {
        {101, 201},  // Should include point (100, 200) = 5
        {301, 151},  // Should include (100, 200) and (300, 150) = 5 + 3 = 8
        {301, 401},  // Should include (100, 200), (300, 150), (100, 400) = 5 + 3 + 7 = 15
        {501, 201},  // Should include (100, 200), (300, 150), (500, 200) = 5 + 3 + 2 = 10
        {1000, 1000} // Should include all points = 5 + 3 + 7 + 2 + 4 + 6 = 27
    };
    
    for (auto [qx, qy] : query_points) {
        ll sum = ft2d.query(qx, qy);
        cout << "Sum in rectangle (0,0) to (" << qx << "," << qy << "): " << sum << endl;
    }
    
    // Phase 4: Arbitrary rectangle queries
    cout << "\n--- Phase 4: Arbitrary Rectangle Queries ---" << endl;
    
    // To query sum in rectangle from (x1,y1) to (x2,y2) (both inclusive):
    // sum = query(x2+1, y2+1) - query(x1, y2+1) - query(x2+1, y1) + query(x1, y1)
    
    auto rectangle_query = [&](int x1, int y1, int x2, int y2) -> ll {
        return ft2d.query(x2 + 1, y2 + 1) - ft2d.query(x1, y2 + 1) 
               - ft2d.query(x2 + 1, y1) + ft2d.query(x1, y1);
    };
    
    // Query rectangle from (200, 100) to (400, 500)
    ll rect_sum = rectangle_query(200, 100, 400, 500);
    cout << "Sum in rectangle (200,100) to (400,500): " << rect_sum << endl;
    // Should include points (300, 150) and (300, 400) if it exists
    
    // Query rectangle from (0, 0) to (300, 300)
    rect_sum = rectangle_query(0, 0, 300, 300);
    cout << "Sum in rectangle (0,0) to (300,300): " << rect_sum << endl;
    // Should include (100, 200), (300, 150)
    
    // Phase 5: Point updates
    cout << "\n--- Phase 5: Point Updates ---" << endl;
    
    // Update existing point (100, 200) by adding 10 more
    ft2d.update(100, 200, 10);
    cout << "Added 10 to point (100, 200)" << endl;
    
    // Query to see the change
    ll new_sum = ft2d.query(101, 201);
    cout << "New sum including point (100, 200): " << new_sum << endl;
    // Should be 15 (original 5 + added 10)
    
    // Phase 6: Practical example - Count points in rectangles
    cout << "\n--- Phase 6: Counting Points in Rectangles ---" << endl;
    
    // Reset and use for counting (each point has value 1)
    FT2 counter(1001);
    
    vector<pair<int, int>> count_points = {
        {50, 50}, {150, 150}, {250, 250}, {350, 350}, {450, 450}
    };
    
    // Setup coordinate compression for counting
    for (auto [x, y] : count_points) {
        counter.fakeUpdate(x, y);
    }
    counter.init();
    
    // Add points with value 1 (for counting)
    for (auto [x, y] : count_points) {
        counter.update(x, y, 1);
        cout << "Added point (" << x << ", " << y << ")" << endl;
    }
    
    // Count points in rectangle (0, 0) to (300, 300)
    ll point_count = counter.query(301, 301);
    cout << "Number of points in rectangle (0,0) to (300,300): " << point_count << endl;
    
    return 0;
}