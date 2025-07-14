#include <bits/stdc++.h>
using namespace std;

/// Extended Euclidean Algorithm
/// Find gcd(a, b) and x, y such that ax + by = gcd(a, b)
/// Returns gcd(a, b)
template<typename T>
T extgcd(T a, T b, T &x, T &y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    T g = extgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return g;
}

/// Return true if there exist such (x, y) satisfy ax + by = c
/// Find (&g) = gcd(a, b)
/// Find (&x, &y) satisfy ax + by = c
template<typename T>
bool find_any_solution(T a, T b, T c, T &x, T &y, T &g){
    if (a == 0 && b == 0) { // 0x + 0y = c
        if (c != 0) return false;
        x = y = g = 0;
        return true;
    }
    if (a == 0) { // 0x + by = c
        if (c % b != 0) return false;
        x = 0, y = c / b, g = abs(b);
        return true;
    }
    if (b == 0) { // ax + 0y = c
        if (c % a != 0) return false;
        x = c / a, y = 0, g = abs(a);
        return true;
    }
    /// ax + by = c
    g = extgcd(abs(a), abs(b), x, y);
    if (c % g != 0) return false;
    x *= (a < 0 ? -1 : +1) * c / g;
    y *= (b < 0 ? -1 : +1) * c / g;
    return true;
}