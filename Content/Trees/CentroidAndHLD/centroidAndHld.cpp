#include <bits/stdc++.h>
using namespace std;

/* ===========================================================================
 *  CENTROID DECOMPOSITION                                    O(N log N) build
 * ---------------------------------------------------------------------------
 *  Idea: a centroid is a vertex whose removal leaves components of size <= N/2.
 *  Remove it, recurse on each component. The centroids form a "centroid tree"
 *  of depth O(log N). Any path u-v in the original tree passes through the
 *  centroid-tree LCA of u and v  ->  "paths through a vertex" divide & conquer.
 *
 *  Uses: count/aggregate paths with a property (length == K, sum <= K, ...),
 *        nearest marked vertex queries with updates, dist-based queries
 *        (sum of dists to marked set), any "for every path..." counting.
 *
 *  Everything is iterative (no recursion depth problems), 0-indexed.
 *
 *  Provided data after build():
 *    cpar[v]       parent of v in centroid tree (-1 for root centroid)
 *    clevel[v]     depth of v in centroid tree (root centroid = 0)
 *    distAnc[v][k] distance in ORIGINAL tree from v to its centroid ancestor
 *                  at level k  (k = 0..clevel[v]; distAnc[v][clevel[v]] = 0).
 *                  Memory N log N; delete if you don't need it.
 * ========================================================================= */
struct CentroidDecomposition {
    int n;
    vector<vector<int>> g;
    vector<int> cpar, clevel, sz, tmpPar, tmpDist, bfs;
    vector<char> dead;                 // dead[v] = v already chosen as centroid
    vector<vector<int>> distAnc;

    explicit CentroidDecomposition(int n)
        : n(n), g(n), cpar(n, -1), clevel(n, 0), sz(n), tmpPar(n),
          tmpDist(n), dead(n, 0), distAnc(n) {}

    void addEdge(int u, int v) { g[u].push_back(v); g[v].push_back(u); }

    // Centroid of the (alive) component containing `root`.
    int findCentroid(int root) {
        bfs.clear(); bfs.push_back(root); tmpPar[root] = -1;
        for (size_t i = 0; i < bfs.size(); i++) {      // BFS order of component
            int u = bfs[i]; sz[u] = 1;
            for (int v : g[u])
                if (v != tmpPar[u] && !dead[v]) { tmpPar[v] = u; bfs.push_back(v); }
        }
        for (int i = (int)bfs.size() - 1; i > 0; i--)  // subtree sizes bottom-up
            sz[tmpPar[bfs[i]]] += sz[bfs[i]];
        int total = bfs.size(), c = root;
        while (true) {                                  // walk towards heavy child
            bool moved = false;
            for (int v : g[c])
                if (v != tmpPar[c] && !dead[v] && 2 * sz[v] > total) { c = v; moved = true; break; }
            if (!moved) return c;
        }
    }

    // process(c) is called once per centroid c, BEFORE c is removed:
    //   - the alive component of c (all vertices with !dead[]) is exactly the
    //     part of the tree this centroid is responsible for,
    //   - c itself is still alive, so DFS/BFS from c covers the whole component.
    // Typical process(): DFS from c, collect (depth, value) of each vertex,
    // combine, and subtract same-child-subtree contributions (inclusion-exclusion).
    template <class F> void build(F process) {
        vector<array<int, 3>> st;                       // {root of comp, centroid parent, level}
        st.push_back({0, -1, 0});
        while (!st.empty()) {
            auto [r, p, lvl] = st.back(); st.pop_back();
            int c = findCentroid(r);
            cpar[c] = p; clevel[c] = lvl;

            bfs.clear(); bfs.push_back(c); tmpPar[c] = -1; tmpDist[c] = 0;
            for (size_t i = 0; i < bfs.size(); i++) {   // dist from c to its component
                int u = bfs[i];
                distAnc[u].push_back(tmpDist[u]);       // index == lvl (top-down order)
                for (int v : g[u])
                    if (v != tmpPar[u] && !dead[v]) { tmpPar[v] = u; tmpDist[v] = tmpDist[u] + 1; bfs.push_back(v); }
            }

            process(c);
            dead[c] = 1;
            for (int v : g[c]) if (!dead[v]) st.push_back({v, c, lvl + 1});
        }
    }
    void build() { build([](int) {}); }                 // just build the centroid tree
};

/* --- EXAMPLE: nearest marked vertex, mark(v) / query(v) in O(log N) ----------
 *   CentroidDecomposition cd(n);  (addEdge...)  cd.build();
 *   const int INF = 1e9;
 *   vector<int> best(n, INF);   // best[a] = min dist from centroid a to a marked vertex in its comp
 *   auto mark = [&](int v) {
 *       for (int a = v; a != -1; a = cd.cpar[a])
 *           best[a] = min(best[a], cd.distAnc[v][cd.clevel[a]]);
 *   };
 *   auto query = [&](int v) {
 *       int res = INF;
 *       for (int a = v; a != -1; a = cd.cpar[a])
 *           res = min(res, best[a] + cd.distAnc[v][cd.clevel[a]]);
 *       return res;
 *   };
 *
 * --- EXAMPLE: count paths of length exactly K (process(c) skeleton) ---------
 *   cnt[d] = number of vertices at depth d seen so far from c (cnt[0] = 1 for c).
 *   for each child v of c (alive): DFS v collecting depths list L;
 *       ans += sum over d in L of cnt[K - d];   // pair with previous subtrees
 *       then add L into cnt.                     // so same-subtree pairs not counted
 *   clear cnt afterwards (only up to max depth, to keep O(size) per centroid).
 * ------------------------------------------------------------------------- */


/* ===========================================================================
 *  HEAVY-LIGHT DECOMPOSITION                    O(N) build, O(log N) LCA,
 *                                               O(log^2 N) path query w/ seg tree
 * ---------------------------------------------------------------------------
 *  Idea: heavy child = child with the largest subtree. Heavy edges form
 *  vertical chains. Any root->v path crosses only O(log N) light edges, hence
 *  touches O(log N) chains. If positions are assigned by DFS visiting the
 *  heavy child FIRST, then
 *      - every chain is a contiguous range [pos[head], pos[bottom]]
 *      - every subtree is a contiguous range [pos[v], pos[v] + sz[v] - 1]
 *  so a path = O(log N) ranges, a subtree = 1 range -> use segment tree / BIT.
 *
 *  Uses: path sum/max/min/gcd with point or range updates, subtree queries,
 *        LCA without binary lifting, edge-weighted path queries,
 *        "add x on path, query on path/subtree" problems.
 *
 *  Iterative (no recursion), 0-indexed. Works on a forest if you call build()
 *  per root (pos continues from `timer`) - for a single tree just build(0).
 * ========================================================================= */
struct HLD {
    int n, timer = 0;
    vector<vector<int>> g;
    vector<int> par, depth, sz, heavy, head, pos, vertAt;   // vertAt[pos] = vertex

    explicit HLD(int n)
        : n(n), g(n), par(n, -1), depth(n, 0), sz(n, 1), heavy(n, -1),
          head(n, 0), pos(n, 0), vertAt(n, 0) {}

    void addEdge(int u, int v) { g[u].push_back(v); g[v].push_back(u); }

    void build(int root = 0) {
        // 1) BFS order -> parent, depth
        vector<int> order; order.reserve(n);
        order.push_back(root); par[root] = -1; depth[root] = 0;
        for (size_t i = 0; i < order.size(); i++) {
            int u = order[i];
            for (int v : g[u])
                if (v != par[u]) { par[v] = u; depth[v] = depth[u] + 1; order.push_back(v); }
        }
        // 2) sizes + heavy child, bottom-up
        for (int i = (int)order.size() - 1; i > 0; i--) {
            int v = order[i], p = par[v];
            sz[p] += sz[v];
        }
        for (int u : order) {
            int best = 0;
            for (int v : g[u])
                if (v != par[u] && sz[v] > best) { best = sz[v]; heavy[u] = v; }
        }
        // 3) preorder with heavy child visited first (pushed LAST on the stack)
        vector<int> st = {root}; head[root] = root;
        while (!st.empty()) {
            int u = st.back(); st.pop_back();
            pos[u] = timer; vertAt[timer++] = u;
            for (int v : g[u])
                if (v != par[u] && v != heavy[u]) { head[v] = v; st.push_back(v); }
            if (heavy[u] != -1) { head[heavy[u]] = head[u]; st.push_back(heavy[u]); }
        }
    }

    int lca(int u, int v) const {
        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]]) swap(u, v);
            u = par[head[u]];
        }
        return depth[u] < depth[v] ? u : v;
    }
    int dist(int u, int v) const { return depth[u] + depth[v] - 2 * depth[lca(u, v)]; }

    // Calls f(l, r) on O(log N) inclusive position ranges covering path u..v.
    //   edges = false: values live on vertices.
    //   edges = true : value of edge (child, parent) is stored at pos[child];
    //                  the LCA's position is excluded.
    // NOTE: ranges come in arbitrary order (not u->v). For NON-commutative
    // operations collect the segments and orient them yourself.
    template <class F> void processPath(int u, int v, F f, bool edges = false) const {
        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]]) swap(u, v);
            f(pos[head[u]], pos[u]);
            u = par[head[u]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        if (pos[u] + edges <= pos[v]) f(pos[u] + edges, pos[v]);
    }

    // Subtree of v is the single range [pos[v], pos[v] + sz[v] - 1]
    template <class F> void processSubtree(int v, F f) const {
        f(pos[v], pos[v] + sz[v] - 1);
    }
};

/* --- Minimal segment tree to pair with HLD (point update, range sum) -------
 *  Swap `+` / 0 for max / min / gcd as needed. Half-open [l, r) internally. */
struct SegTree {
    int n; vector<long long> t;
    explicit SegTree(int n) : n(n), t(2 * n, 0) {}
    void set(int p, long long x) { for (t[p += n] = x; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1]; }
    long long query(int l, int r) {                 // inclusive [l, r]
        long long res = 0;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res += t[l++];
            if (r & 1) res += t[--r];
        }
        return res;
    }
};

/* --- EXAMPLE: vertex values, path sum + point update + subtree sum ----------
 *   HLD h(n); (addEdge...); h.build(0);
 *   SegTree st(n);
 *   for (int v = 0; v < n; v++) st.set(h.pos[v], a[v]);
 *   // update vertex v to x:
 *   st.set(h.pos[v], x);
 *   // path sum u..v:
 *   long long s = 0; h.processPath(u, v, [&](int l, int r) { s += st.query(l, r); });
 *   // subtree sum of v:
 *   long long t = 0; h.processSubtree(v, [&](int l, int r) { t += st.query(l, r); });
 *
 * --- EXAMPLE: edge weights: for edge (p, c) with c the deeper endpoint
 *   st.set(h.pos[c], w);   and query with processPath(u, v, f, true)  [true = edges mode].
 * ------------------------------------------------------------------------- */