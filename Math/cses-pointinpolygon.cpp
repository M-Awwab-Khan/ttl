#include <bits/stdc++.h>
using namespace std;

using ll = long long;
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

// Orientation: 0 = colinear, 1 = ccw, -1 = cw
int orient(const Point& a, const Point& b, const Point& c) {
    return sgn((b - a).cross(c - a));
}

// Check if c lies on segment ab
bool onSegment(Point a, Point b, Point c) {
    return orient(a, b, c) == 0 && sgn((a - c).dot(b - c)) <= 0;
}


// Point in polygon (0 = outside, 1 = boundary, 2 = inside)
int inPolygon(const vector<Point>& poly, Point p) {
    int n = poly.size(), cnt = 0;
    for (int i = 0; i < n; ++i) {
        Point a = poly[i], b = poly[(i + 1) % n];
        if (onSegment(a, b, p)) return 1;
        if (sgn(a.y - b.y) == 0) continue;
        if (p.y < min(a.y, b.y) || p.y >= max(a.y, b.y)) continue;
        ld x = (p.y - a.y) * (b.x - a.x) / (b.y - a.y) + a.x;
        if (x > p.x) cnt++;
    }    
    return cnt % 2 ? 2 : 0;
}    


int main() {
    int n, m; cin >> n >> m;

    vector<Point> points(n);
    for (int i = 0; i < n; ++i) {
        cin >> points[i].x >> points[i].y;
    }

    for (int i = 0; i < m; ++i) {
        Point p;
        cin >> p.x >> p.y;
        int res = inPolygon(points, p);
        if (res == 0) {
            cout << "OUTSIDE" << endl;
        } else if (res == 1) {
            cout << "BOUNDARY" << endl;
        } else {
            cout << "INSIDE" << endl;
        }
    }
}