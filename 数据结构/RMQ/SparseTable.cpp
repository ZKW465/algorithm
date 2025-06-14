template<typename T, 
    typename Cmp = less<T>>
struct RMQ {
    int n;
    vector<vector<T>> pre;
    Cmp cmp;
    RMQ() = default;
    RMQ(vector<T>& c) {
        init(c);
    }
    void init(vector<T>& c) {
        n = c.size();
        int k = __lg(n) + 1;
        pre.assign(k, {});
        pre[0] = c;
        for (int i = 1, sz = 2; i < k; i += 1, sz *= 2) {
            pre[i].assign(n, 0);
            for (int j = 0; j + sz - 1 < n; j ++) {
                pre[i][j] = std::max(pre[i - 1][j], pre[i - 1][j + sz / 2], cmp);
            }
        }
    }
    T operator()(int l, int r) {
        T k = __lg(r - l + 1);
        return std::max(pre[k][l], pre[k][r - (1 << k) + 1], cmp);
    }
};