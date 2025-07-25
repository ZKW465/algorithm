template<typename T>
struct DSU {
    std::vector<int> f, siz;
    std::vector<T> val;
    
    DSU() {}
    DSU(int n) {
        init(n);
    }
    
    void init(int n) {
        f.resize(n);
        std::iota(f.begin(), f.end(), 0);
        siz.assign(n, 1);
        val.resize(n);
    }
    
    int find(int x) {
        if (x == f[x]) {
            return x;
        }
        int y = f[x];
        f[x] = find(f[x]);
        val[x] += val[y];
        return f[x];
    }
    
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    
    bool unite(int x, int y, T c) {
        int u = find(x);
        int v = find(y);
        if (u == v) {
            return false;
        }
        siz[u] += siz[v];
        f[v] = u;
        val[v] = -val[y] + val[x] + c;
        return true;
    }
    
    int size(int x) {
        return siz[find(x)];
    }

    T Val(int x) {
        find(x);
        return val[x];
    }
};