#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <tuple>
using namespace std;

// Geometry (2D) - Point, Line, Vector, Polygon - Template Version
template <class T> int sgn(T x) { return (x > 0) - (x < 0); }

template<class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
    
    bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
    P operator+(P p) const { return P(x + p.x, y + p.y); }
    P operator-(P p) const { return P(x - p.x, y - p.y); }
    P operator*(T d) const { return P(x * d, y * d); }
    P operator/(T d) const { return P(x / d, y / d); }
    
    T dot(P p) const { return x * p.x + y * p.y; }
    T cross(P p) const { return x * p.y - y * p.x; }
    T cross(P a, P b) const { return (a - *this).cross(b - *this); }
    T dist2() const { return x * x + y * y; }
    double dist() const { return sqrt((double)dist2()); }
    
    // angle to x-axis in interval [-pi, pi]
    double angle() const { return atan2(y, x); }
    P unit() const { return *this / dist(); } // makes dist()=1
    P perp() const { return P(-y, x); } // rotates +90 degrees
    P normal() const { return perp().unit(); }
    
    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const {
        return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    }
    
    friend ostream& operator<<(ostream& os, P p) {
        return os << "(" << p.x << "," << p.y << ")";
    }
};

template<class T>
double dist(Point<T> a, Point<T> b) { return (a - b).dist(); }

template<class T>
double angle(Point<T> a, Point<T> b) { return atan2(a.cross(b), a.dot(b)); }

// Check if three points are collinear
template<class T>
bool collinear(Point<T> a, Point<T> b, Point<T> c) {
    return sgn((b - a).cross(c - a)) == 0;
}

// Orientation: 0 = colinear, 1 = ccw, -1 = cw
template<class T>
int orient(Point<T> a, Point<T> b, Point<T> c) {
    return sgn((b - a).cross(c - a));
}

// Check if c lies on segment ab
template<class T>
bool onSegment(Point<T> a, Point<T> b, Point<T> c) {
    return orient(a, b, c) == 0 && sgn((a - c).dot(b - c)) <= 0;
}

// Line intersection (returns true if intersects)
template<class T>
bool lineInter(Point<T> a, Point<T> b, Point<T> c, Point<T> d, Point<T>& inter) {
    T det = (b - a).cross(d - c);
    if (sgn(det) == 0) return false; // parallel
    inter = a + (b - a) * ((c - a).cross(d - c) / det);
    return true;
}

// Segment intersection (returns true if segments intersect)
template<class T>
bool segmentInter(Point<T> a, Point<T> b, Point<T> c, Point<T> d) {
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

// Polygon Area (CCW or CW doesn't matter)
template<class T>
T polyArea(const vector<Point<T>>& poly) {
    T area = 0;
    int n = poly.size();
    for (int i = 0; i < n; ++i)
        area += poly[i].cross(poly[(i + 1) % n]);
    return abs(area) / 2;
}

// Convex Hull (Andrew's Monotone Chain, O(n log n))
template<class T>
vector<Point<T>> convexHull(vector<Point<T>> pts) {
    sort(pts.begin(), pts.end());
    int n = pts.size();
    if (n <= 1) return pts;
    vector<Point<T>> hull;
    for (int i = 0; i < n; ++i) {
        while (hull.size() >= 2 && orient(hull[hull.size()-2], hull[hull.size()-1], pts[i]) <= 0) {
            hull.pop_back();
        }
        hull.push_back(pts[i]);
    }
    int lower_size = hull.size();
    for (int i = n - 2; i >= 0; --i) {
        while (hull.size() > lower_size && orient(hull[hull.size()-2], hull[hull.size()-1], pts[i]) <= 0) {
            hull.pop_back();
        }
        hull.push_back(pts[i]);
    }
    if (hull.size() > 1) hull.pop_back();
    return hull;
}

// Point in polygon (0 = outside, 1 = boundary, 2 = inside)
template<class T>
int inPolygon(const vector<Point<T>>& poly, Point<T> p) {
    int n = poly.size(), cnt = 0;
    for (int i = 0; i < n; ++i) {
        Point<T> a = poly[i], b = poly[(i + 1) % n];
        if (onSegment(a, b, p)) return 1;
        if (sgn(a.y - b.y) == 0) continue;
        if (p.y < min(a.y, b.y) || p.y >= max(a.y, b.y)) continue;
        T x = (p.y - a.y) * (b.x - a.x) / (b.y - a.y) + a.x;
        if (x > p.x) cnt++;
    }
    return cnt % 2 ? 2 : 0;
}

int main() {
    cout << fixed << setprecision(6);
    
    // Example usage:
    typedef Point<long long> P;
    
    int n; cin >> n;
    vector<P> points(n);
    for (int i = 0; i < n; ++i) {
        cin >> points[i].x >> points[i].y;
    }

    cout << polyArea(points) * 2 << endl;
    
    return 0;
}