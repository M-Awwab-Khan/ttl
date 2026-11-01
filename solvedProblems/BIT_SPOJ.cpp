#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct SegTree {
    int n;
    vector<T> tree;
    function<T(const T&, const T&)> merge;
    T identity;

    SegTree(int n, function<T(const T&, const T&)> mergeFunc, T identity)
        : n(n), merge(mergeFunc), identity(identity) {
        tree.assign(4 * n, identity);
    }

    void build(const vector<T> &arr, int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = arr[tl];
            return;
        }
        int tm = (tl + tr) / 2;
        build(arr, v*2, tl, tm);
        build(arr, v*2+1, tm+1, tr);
        tree[v] = merge(tree[v*2], tree[v*2+1]);
    }

    void build(const vector<T> &arr) {
        build(arr, 1, 0, n-1);
    }

    void update(int v, int tl, int tr, int pos, T val) {
        if (tl == tr) {
            tree[v] = val;
            return;
        }
        int tm = (tl + tr) / 2;
        if (pos <= tm) update(v*2, tl, tm, pos, val);
        else update(v*2+1, tm+1, tr, pos, val);
        tree[v] = merge(tree[v*2], tree[v*2+1]);
    }

    void update(int pos, T val) {
        update(1, 0, n-1, pos, val);
    }

    void add(int v, int tl, int tr, int pos, T val) {
        if (tl == tr) {
            tree[v] += val;
            return;
        }
        int tm = (tl + tr) / 2;
        if (pos <= tm) add(v*2, tl, tm, pos, val);
        else add(v*2+1, tm+1, tr, pos, val);
        tree[v] = merge(tree[v*2], tree[v*2+1]);
    }

    void add(int pos, T val) {
        add(1, 0, n-1, pos, val);
    }

    T query(int v, int tl, int tr, int l, int r) {
        if (l > r) return identity;
        if (l <= tl && tr <= r) return tree[v];
        int tm = (tl + tr) / 2;
        return merge(
            query(v*2, tl, tm, l, min(r, tm)),
            query(v*2+1, tm+1, tr, max(l, tm+1), r)
        );
    }

    T query(int l, int r) {
        return query(1, 0, n-1, l, r);
    }
};


int main() {
     ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t; cin >> t; while(t--) {


        int n; cin >> n;

        vector<int> a(n); for(int i = 0; i < n; ++i) cin >> a[i];

        int mx = *max_element(a.begin(), a.end());

        SegTree<long long> seg(mx + 2, [&](const long long &a, const long long &b) {return a + b;}, 0);

        long long ans = 0;
        for(int i = 0; i < n ; ++i) {
            ans += seg.query(0, a[i]-1);
            seg.add(a[i], a[i]);
        } 
        cout << ans << "\n";
    }
}