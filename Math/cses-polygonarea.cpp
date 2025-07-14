#include <bits/stdc++.h>
using namespace std;

// Geometry (2D) - Point, Line, Vector, Polygon
using ll = long long;

struct Point {
    ll x, y;
    Point(ll x = 0, ll y = 0) : x(x), y(y) {}
    
    Point operator+(const Point& p) const { return {x + p.x, y + p.y}; }
    Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
    Point operator*(ll d) const { return {x * d, y * d}; }
    Point operator/(ll d) const { return {x / d, y / d}; }

    bool operator==(const Point& p) const { return x == p.x && y == p.y; }
    bool operator<(const Point& p) const { return x != p.x ? x < p.x : y < p.y; }

    ll cross(const Point& p) const { return x * p.y - y * p.x; }
};

// Polygon Area (returns 2 * actual area to avoid floating point)
ll polyArea(const vector<Point>& poly) {
    ll area = 0;
    int n = poly.size();
    for (int i = 0; i < n; ++i)
        area += poly[i].cross(poly[(i + 1) % n]);
    return abs(area);
}

int main() {
    int n; 
    cin >> n;
    vector<Point> points(n);
    for (int i = 0; i < n; ++i) {
        cin >> points[i].x >> points[i].y;
    }

    cout << polyArea(points) << endl;
    
    return 0;
}