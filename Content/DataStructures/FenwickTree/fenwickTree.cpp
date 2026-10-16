// Use 1 based indexing
long long sum(vll& tr, ll k) {
    ll s = 0;
    while(k >= 1) {
        s += tr[k];
        k -= k&-k;
    }
    return s;
}

void add(vll& tr, ll k, ll x) {
    while(k < tr.size()) {
        tr[k] += x;
        k += k&-k;
    }
}