template<typename T>
struct Graph {
    int n;
    struct edge {
        int u, v;
        T val;
        friend ostream& operator<<(ostream& cout, edge e) {
            return cout << "{" << e.u << ", " << e.v << ", " << e.val << "}";
        }
    };
    vector<edge> E;
    Graph(int n) : n(n + 1) {};
    // x + val <= y
    void add(int x, int y, T val) {
        E.emplace_back(x, y, val);
    }
    // x + val == y
    void equal(int x, int y, int val) {
        add(x, y, val);
        add(y, x, -val);
    }
    std::optional<vector<T>> Ford() {
        vector<T> dis;
        for (int i = 0; i < n; i++) {
            add(n, i, 0);
        }
        dis.assign(n + 1, 0);
        int ok = true;
        for (int i = 0; i <= n && ok; i++) {
            ok = false;
            for (auto [l, r, w] : E) {
                if (dis[r] < dis[l] + w) {
                    ok = true;
                    dis[r] = dis[l] + w;
                }
            }
        }
        return ok ? std::nullopt : optional(dis);
    }
};