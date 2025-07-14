#include <bits/stdc++.h>
using namespace std;


using ld = long double;
const ld EPS = 1e-9, PI = acos(-1);

int sgn(ld x) { return (x > EPS) - (x < -EPS); }

struct Point {
    ld x, y;
    Point(ld x = 0, ld y = 0) : x(x), y(y) {}
    
    Point operator+(const Point& p) const { return {x + p.x, y + p.y}; }
    Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
    Point operator*(ld d) const { return {x * d, y * d}; }
    Point operator/(ld d) const { return {x / d, y / d}; }

    bool operator==(const Point& p) const { return sgn(x - p.x) == 0 && sgn(y - p.y) == 0; }
    bool operator<(const Point& p) const { return sgn(x - p.x) ? x < p.x : y < p.y; }

    ld dot(const Point& p) const { return x * p.x + y * p.y; }
    ld cross(const Point& p) const { return x * p.y - y * p.x; }
    ld norm() const { return x * x + y * y; }
    ld len() const { return sqrtl(norm()); }
    Point perp() const { return {-y, x}; } // 90 deg CCW
    Point unit() const { return *this / len(); }
};

// Orientation: 0 = collinear, 1 = ccw, -1 = cw
int orient(const Point& a, const Point& b, const Point& c) {
    return sgn((b - a).cross(c - a));
}

// Check if point c lies on segment ab
bool onSegment(Point a, Point b, Point c) {
    return orient(a, b, c) == 0 && sgn((a - c).dot(b - c)) <= 0;
}

// Segment intersection (returns true if segments intersect)
bool segmentInter(Point a, Point b, Point c, Point d) {
    int o1 = orient(a, b, c);
    int o2 = orient(a, b, d);
    int o3 = orient(c, d, a);
    int o4 = orient(c, d, b);
    if (o1 != o2 && o3 != o4) return true;
    if (o1 == 0 && onSegment(a, b, c)) return true;
    if (o2 == 0 && onSegment(a, b, d)) return true;
    if (o3 == 0 && onSegment(c, d, a)) return true;
    if (o4 == 0 && onSegment(c, d, b)) return true;
    return false;
}


void solve() {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    Point p1(x1, y1), p2(x2, y2);

    int x3, y3, x4, y4;
    cin >> x3 >> y3 >> x4 >> y4;
    Point p3(x3, y3), p4(x4, y4);

    bool intersects = segmentInter(p1, p2, p3, p4);
    if (intersects) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}

int main() {
    int t; cin >> t;
    while (t--) {
        solve();
    }
}