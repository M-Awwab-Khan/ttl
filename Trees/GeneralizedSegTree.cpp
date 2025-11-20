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
    vector<int> data = {1, 3, 5, 7, 9, 11};
    SegTree<int> segTree(data.size(),
                         [](const int &a, const int &b) { return a + b; },
                         0);
    segTree.build(data);

    cout << segTree.query(1, 3) << endl; // Output: 15 (3 + 5 + 7)
    segTree.update(1, 10); // Update index 1 to value 10
    cout << segTree.query(1, 3) << endl; // Output: 22 (10 + 5 + 7)

    return 0;
}
