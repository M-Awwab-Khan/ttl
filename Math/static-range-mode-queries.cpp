#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;   // candidate value
    int cnt;   // weight (vote count)
};

struct SegTree {
    int n;
    vector<Node> st;

    SegTree(int n) : n(n), st(4*n) {}

    Node merge(Node a, Node b) {
        if (a.val == b.val) return {a.val, a.cnt + b.cnt};
        if (a.cnt > b.cnt)  return {a.val, a.cnt - b.cnt};
        return {b.val, b.cnt - a.cnt};
    }

    void build(vector<int> &a, int p, int l, int r) {
        if (l == r) {
            st[p] = {a[l], 1};
            return;
        }
        int m = (l + r) >> 1;
        build(a, 2*p, l, m);
        build(a, 2*p+1, m+1, r);
        st[p] = merge(st[2*p], st[2*p+1]);
    }

    Node query(int p, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return {0, 0};  // identity
        if (ql <= l && r <= qr) return st[p];
        int m = (l + r) >> 1;
        return merge(
            query(2*p, l, m, ql, qr),
            query(2*p+1, m+1, r, ql, qr)
        );
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    vector<int> a(N+1);
    for (int i = 1; i <= N; i++) cin >> a[i];

    // store positions of each crop type
    unordered_map<int, vector<int>> pos;
    pos.reserve(N * 2);

    for (int i = 1; i <= N; i++)
        pos[a[i]].push_back(i);

    // build segment tree
    SegTree st(N);
    st.build(a, 1, 1, N);

    while (Q--) {
        int L, R;
        cin >> L >> R;

        Node cand = st.query(1, 1, N, L, R);
        int x = cand.val;

        // candidate might be invalid (0-count identity)
        if (cand.cnt == 0) {
            cout << 0 << "\n";
            continue;
        }

        auto &v = pos[x];

        // count freq of x in [L, R]
        int freq = upper_bound(v.begin(), v.end(), R)
                 - lower_bound(v.begin(), v.end(), L);

        int len = R - L + 1;

        if (freq * 2 > len) cout << x << "\n";
        else cout << 0 << "\n";
    }

    return 0;
}
