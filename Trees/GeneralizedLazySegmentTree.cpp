#include <bits/stdc++.h>
using namespace std;

/*
 T  = node type     (ex: long long)
 L  = lazy type     (ex: long long)
 merge(T, T) -> T               combines child nodes
 apply(T, L, int len) -> T      applies lazy value to node
 compose(L, L) -> L             combines lazy values
 IDT = identity for T
 IDL = identity for L
*/

template<typename T, typename L>
struct LazySegTree {
    int n;
    vector<T> tree;
    vector<L> lazy;
    function<T(const T&, const T&)> merge;
    function<T(const T&, const L&, int)> apply;
    function<L(const L&, const L&)> compose;
    T IDT; // identity element for T
    L IDL; // identity element for L

    LazySegTree(int n,
                function<T(const T&, const T&)> merge,
                function<T(const T&, const L&, int)> apply,
                function<L(const L&, const L&)> compose,
                T IDT, L IDL)
        : n(n), merge(merge), apply(apply), compose(compose),
          IDT(IDT), IDL(IDL) 
    {
        tree.assign(4*n, IDT);
        lazy.assign(4*n, IDL);
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

    void push(int v, int tl, int tr) {
        if (lazy[v] == IDL) return; // nothing to push
        int tm = (tl + tr) / 2;

        // push to children
        tree[v*2]     = apply(tree[v*2],     lazy[v], tm - tl + 1);
        tree[v*2 + 1] = apply(tree[v*2 + 1], lazy[v], tr - tm);

        lazy[v*2]     = compose(lazy[v*2],     lazy[v]);
        lazy[v*2 + 1] = compose(lazy[v*2 + 1], lazy[v]);

        lazy[v] = IDL;
    }

    void update(int v, int tl, int tr, int l, int r, L val) {
        if (l > r) return;

        if (l <= tl && tr <= r) {
            tree[v] = apply(tree[v], val, tr - tl + 1);
            lazy[v] = compose(lazy[v], val);
            return;
        }

        push(v, tl, tr);
        int tm = (tl + tr) / 2;

        update(v*2, tl, tm, l, min(r, tm), val);
        update(v*2+1, tm+1, tr, max(l, tm+1), r, val);

        tree[v] = merge(tree[v*2], tree[v*2+1]);
    }

    void update(int l, int r, L val) {
        update(1, 0, n-1, l, r, val);
    }

    T query(int v, int tl, int tr, int l, int r) {
        if (l > r) return IDT;

        if (l <= tl && tr <= r) return tree[v];

        push(v, tl, tr);
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
    // Example usage: Range Sum with Range Addition
    int n = 10;
    LazySegTree<long long, long long> segtree(
        n,
        [](const long long &a, const long long &b) { return a + b; }, // merge
        [](const long long &node, const long long &lazy, int len) { return node + lazy * len; }, // apply
        [](const long long &a, const long long &b) { return a + b; }, // compose
        0LL, // IDT
        0LL  // IDL
    );

    vector<long long> arr(n, 0);
    segtree.build(arr);

    segtree.update(0, 4, 5); // Add 5 to range [0, 4] the array becomes [5,5,5,5,5,0,0,0,0,0]
    segtree.update(2, 6, 3); // Add 3 to range [2, 6] the array becomes [5,5,8,8,8,3,3,0,0,0]

    cout << segtree.query(0, 4) << endl; // Query sum in range [0, 4]
    cout << segtree.query(5, 9) << endl; // Query sum in range [5, 9]


    // Example usage: Range Minimum with Range Update
    LazySegTree<long long, long long> minsegtree(
        n,
        [](const long long &a, const long long &b) { return min(a, b); }, // merge
        [](const long long &node, const long long &lazy, int len) { return lazy; }, // apply
        [](const long long &a, const long long &b) { return b; }, // compose
        LLONG_MAX, // IDT
        LLONG_MAX  // IDL
    );

    vector<long long> arr2(n, LLONG_MAX);
    minsegtree.build(arr2);

    minsegtree.update(0, 4, 10); // Set range [0, 4] to 10 the array becomes [10,10,10,10,10,∞,∞,∞,∞,∞]
    minsegtree.update(2, 6, 5);  // Set range [2, 6] to 5 the array becomes [10,10,5,5,5,5,5,∞,∞,∞]

    cout << minsegtree.query(0, 4) << endl; // Query min in range [0, 4]
    cout << minsegtree.query(5, 9) << endl; // Query min in range [5, 9]

    // Example usage: Lazy Range Assign + Range Sum Query
    LazySegTree<long long, long long> assignsegtree(
        n,
        [](const long long &a, const long long &b) { return a + b; }, // merge
        [](const long long &node, const long long &lazy, int len) { return lazy * len; }, // apply
        [](const long long &a, const long long &b) { return b; }, // compose
        0LL, // IDT
        LLONG_MAX  // IDL (using LLONG_MAX to indicate no assignment)
    );

    vector<long long> arr3(n, 0);
    assignsegtree.build(arr3);

    assignsegtree.update(0, 4, 7); // Assign 7 to range [0, 4] the array becomes [7,7,7,7,7,0,0,0,0,0]
    assignsegtree.update(2, 6, 4); // Assign 4 to range [2, 6] the array becomes [7,7,4,4,4,4,4,0,0,0]

    cout << assignsegtree.query(0, 4) << endl; // Query sum in range [0, 4]
    cout << assignsegtree.query(5, 9) << endl; // Query sum in range [5, 9] 


    // Example Usage: Range XOR Update + Range XOR Query
    LazySegTree<long long, long long> xorsegtree(
        n,
        [](const long long &a, const long long &b) { return a ^ b; }, // merge
        [](const long long &node, const long long &lazy, int len) { 
            return (len % 2 == 0) ? node : (node ^ lazy); 
        }, // apply
        [](const long long &a, const long long &b) { return a ^ b; }, // compose
        0LL, // IDT
        0LL  // IDL
    );

    vector<long long> arr4(n, 0);
    xorsegtree.build(arr4);

    xorsegtree.update(0, 4, 6); // XOR 6 to range [0, 4] the array becomes [6,6,6,6,6,0,0,0,0,0]
    xorsegtree.update(2, 6, 3); // XOR 3 to range [2, 6] the array becomes [6,6,5,5,5,3,3,0,0,0]

    cout << xorsegtree.query(0, 4) << endl; // Query XOR in range [0, 4]
    cout << xorsegtree.query(5, 9) << endl; // Query XOR in range [5, 9]

    return 0;
}