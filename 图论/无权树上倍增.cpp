template<class E>
struct csr {
    vector<int> s;
    vector<E> adj;
    csr() = default;
    csr(int n, const vector<pair<int, E>>& g)
        : s(n + 1), adj(g.size()) {
        for (auto e : g) {
            s[e.first + 1]++;
        }
        for (int i = 1; i <= n; i++) {
            s[i] += s[i - 1];
        }
        auto c = s;
        for (auto e : g) {
            adj[c[e.first]++] = e.second;
        }
    }
};

template<int N>
struct Graph {
    int n;
    int K;
    vector<array<int, __lg(N) + 1>> p;
    vector<pair<int, int>> e;
    csr<int> g;
    vector<int> dep;
    Graph() = default;
    Graph(int n) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        dep.assign(n, {});
        p.assign(n, {});
        K = __lg(n) + 1;
    }
    void addEdge(int u, int v) {
        e.push_back({u, v});
        e.push_back({v, u});
    }
    void work(int r = 0) {
        g = csr<int>(n, e);
        dfs(r, r);
    }
    void dfs(int u, int f) {
        p[u][0] = f;
        for (int i = 1; i < K; i++) {
            p[u][i] = p[p[u][i - 1]][i - 1];
        }
        for (int i = g.s[u]; i < g.s[u + 1]; i++) {
            int v = g.adj[i];
            if (v == f) {
                continue;
            }
            dep[v] = dep[u] + 1;
            dfs(v, u);
        }
    }
    int jump(int u, int d) {
        for (; d; d -= 1 << __lg(d)) {
            u = p[u][__lg(d)];
        }
        return u;
    }
    int lca(int u, int v) {
        if (dep[u] < dep[v]) {
            swap(u, v);
        }
        u = jump(u, dep[u] - dep[v]);
        if (u == v) {
            return u;
        }
        for (int i = __lg(dep[u]); i >= 0; i--) {
            if (p[u][i] != p[v][i]) {
                u = p[u][i], v = p[v][i];
            }
        }
        return p[u][0];
    }
    int dist(int u, int v, int m = -1) {
        if (m == -1) {
            m = lca(u, v);
        }
        return dep[u] + dep[v] - 2 * dep[m];
    }
};