template<typename Cmp>
struct value {static i64 x;};

template<>
i64 value<std::less<i64>>::x = std::numeric_limits<i64>::max();
template<>
i64 value<std::greater<i64>>::x = std::numeric_limits<i64>::min();

template<typename Cmp 
        = std::greater<i64>>
struct segment {
    struct line {
        i64 k, b;
        i64 operator()(int x) {
            return 1LL * k * x + b;
        }
    };
    int n;
    vector<line> seg;
    Cmp cmp;
    segment(int n) {
        init(n);
    }
    void init(int n_) {
        n = 2 << __lg(n_);
        seg.assign(2 * n, {0, value<Cmp>::x});
    }
    void modify(int p, int l, int r, int x, int y, line u) {
        if (r <= x || y <= l) {
            return;
        }
        int m = (l + r) / 2;
        if (x <= l && r <= y) {
            if (cmp(u(m), seg[p](m))) {
                std::swap(u, seg[p]);
            } 
            if (cmp(u(l), seg[p](l))) {
                modify(p * 2, l, m, x, y, u);
            } 
            if (cmp(u(r - 1), seg[p](r - 1))) {
                modify(p * 2 + 1, m, r, x, y, u);
            } 
            return;
        }
        modify(p * 2, l, m, x, y, u);
        modify(p * 2 + 1, m, r, x, y, u);
    }
    i64 query(int p, int l, int r, int u) {
        if (r - l == 1) {
            return seg[p](u);
        }
        int m = (l + r) / 2;
        i64 res = seg[p](u);
        if (u < m) {
            return std::min(res, query(p * 2, l, m, u), cmp);
        } else {
            return std::min(res, query(p * 2 + 1, m, r, u), cmp);
        }
    }
};
