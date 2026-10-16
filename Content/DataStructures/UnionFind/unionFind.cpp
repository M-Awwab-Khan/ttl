vi link(n + 1), size(n + 1);
f(i, 1, n + 1) link[i] = i;
f(i, 1, n + 1) size[i] = 1;

int find(int x) {
    if(x == link[x]) return x;
    return link[x] = find(link[x]);
}

bool same(int x, int y) {
    return find(x) == find(y);
}

void union(int a, int b) {
    a = find(a);
    b = find(b);
    if(a != b) {
        if(size[a] < size[b]) swap(a, b);
        size[a] += size[b];
        link[b] = a;
    }
}