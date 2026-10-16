// Set Identity / Base value returns
struct LazySegTree {
    int n;
    vector<ll> t, lz;  // t = sum on segment, lz = pending add for children
    LazySegTree(int n) : n(n), t(4 * n), lz(4 * n) {}
    LazySegTree(const vector<ll>& a) : LazySegTree((int)a.size()) {
        build(1, 0, n, a);
    }
    void build(int v, int l, int r, const vector<ll>& a) {
        if (r - l == 1) { t[v] = a[l]; return; }
        int m = (l + r) / 2;
        build(2 * v, l, m, a);
        build(2 * v + 1, m, r, a);
        t[v] = t[2 * v] + t[2 * v + 1];
    }
    void apply(int v, int l, int r, ll x) {  // apply +x to whole segment
        t[v] += x * (r - l);
        lz[v] += x;
    }
    void push(int v, int l, int r) {
        if (lz[v]) {
            int m = (l + r) / 2;
            apply(2 * v, l, m, lz[v]);
            apply(2 * v + 1, m, r, lz[v]);
            lz[v] = 0;
        }
    }
    void update(int v, int l, int r, int ql, int qr, ll x) {
        if (qr <= l || r <= ql) return;
        if (ql <= l && r <= qr) { apply(v, l, r, x); return; }
        push(v, l, r);
        int m = (l + r) / 2;
        update(2 * v, l, m, ql, qr, x);
        update(2 * v + 1, m, r, ql, qr, x);
        t[v] = t[2 * v] + t[2 * v + 1];
    }
    ll query(int v, int l, int r, int ql, int qr) {
        if (qr <= l || r <= ql) return 0;  // identity
        if (ql <= l && r <= qr) return t[v];
        push(v, l, r);
        int m = (l + r) / 2;
        return query(2 * v, l, m, ql, qr) + query(2 * v + 1, m, r, ql, qr);
    }
    void update(int l, int r, ll x) { update(1, 0, n, l, r, x); }  // a[l..r) += x
    ll query(int l, int r) { return query(1, 0, n, l, r); }        // sum a[l..r)
};