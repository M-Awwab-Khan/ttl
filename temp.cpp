// #include <bits/stdc++.h>
// using namespace std;

// /* TYPES  */
// #define ll long long
// #define pii pair<int, int>
// #define pll pair<long long, long long>
// #define vi vector<int>
// #define vll vector<long long>
// #define mii map<int, int>
// #define si set<int>
// #define sc set<char>

// /* FUNCTIONS */
// #define f(i, s, e) for (long long int i = s; i < e; i++)
// #define fe(i, s, e) for (long long int i = s; i <= e; i++)
// #define fr(i, e, s) for (long long int i = e - 1; i >= s; i--)
// #define pb push_back
// #define eb emplace_back
// #define all(x) x.begin(), x.end()

// /* PRINTS */
// template <class T>
// void print_v(vector<T> &v)
// {
//     for (auto x : v)
//         cout << x << ' ';
// }

// /* UTILS */
// #define MOD 1000000007
// #define PI 3.1415926535897932384626433832795
// #define read(type) readInt<type>()
// ll min(ll a, int b)
// {
//     if (a < b)
//         return a;
//     return b;
// }
// ll min(int a, ll b)
// {
//     if (a < b)
//         return a;
//     return b;
// }
// ll max(ll a, int b)
// {
//     if (a > b)
//         return a;
//     return b;
// }
// ll max(int a, ll b)
// {
//     if (a > b)
//         return a;
//     return b;
// }
// ll gcd(ll a, ll b)
// {
//     if (b == 0)
//         return a;
//     return gcd(b, a % b);
// }
// ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }
// bool prime(ll a)
// {
//     if (a == 1)
//         return 0;
//     for (int i = 2; i <= round(sqrt(a)); ++i)
//         if (a % i == 0)
//             return 0;
//     return 1;
// }
// void yes() { cout << "YES\n"; }
// void no() { cout << "NO\n"; }
// void printCase(int i) { cout << "Case " << i << ": "; }

// unordered_map<string, unordered_set<int>> prefixMap;

// string getSignature(string &s)
// {
//     vi freq(26, 0);
//     for (char c : s)
//     {
//         freq[c - 'a']++;
//     }
//     string sig = "";
//     for (int x : freq)
//     {
//         sig += to_string(x) + '#';
//     }
//     return sig;
// }

// void solve()
// {
//     int n;
//     cin >> n;
//     string s;
//     string prefix;
//     f(i, 0, n)
//     {
//         cin >> s;
//         prefix = "";
//         for (char c : s)
//         {
//             prefix += c;
//             prefixMap[getSignature(prefix)].insert(i);
//         }
//     }

//     int q;
//     cin >> q;
//     while (q--)
//     {
//         cin >> s;
//         int ans = prefixMap[getSignature(s)].size();
//         cout << (ans == 0 ? -1 : ans) << '\n';
//     }
// }

// // Problem Link:

// int main()
// {
//     ios::ios_base::sync_with_stdio(0);
//     cin.tie(NULL);
//     int t = 1;
//     // cin >> t;
//     while (t--)
//     {
//         solve();
//     }
//     return 0;
// }


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
    int t; cin >> t;
    while (t--) {
        int n, q; cin >> n >> q;
    
    
        // range xor and range sum
        LazySegTree<int, int> segTree(
            n, 
            [](const int &a, const int &b)  {return a + b;},
            [](const int &node, const int &lazy, const int len) {
                if (len % 2== 0) return node;
                else return node ^ lazy;
            },
            [](const int &a, const int &b) {return a ^ b;},
            0,
            0
        );
    
        vector<int> a(n, 1);
        segTree.build(a);
        int x = 0;
        for (int z = 0; z < q; ++z) {
            int i, j; cin >> i >> j;
            --i;--j;
            int y = segTree.query(i, j);
            x += y;
            segTree.update(i, j, 1);
    
        }
        cout << x/q << endl;
    }
}