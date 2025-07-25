template<typename T>
T power(T a, i64 b, T res = 1) {
    for (; b; b >>= 1) {
        if (b & 1) {
            res *= a;
        }
        a *= a;
    }
    return res;
};

template<int P>
struct mint {
    int x;
    constexpr mint(i64 x_ = 0) : x(norm(x_ % P)) {}
    template<bool U = true>
    static int norm(int x) {
        if constexpr (U) { if (x < 0) x += P;}
        else { if (x >= P) x -= P;}
        return x;
    }
    mint operator-() {
        mint c;
        c.x = norm(-x);
        return c;
    }
    mint& operator+=(mint v) {
        x = norm<false>(x + v.x);
        return *this;
    }
    mint& operator-=(mint v) {
        x = norm(x - v.x);
        return *this;
    }
    mint& operator*=(mint v) {
        x = 1LL * x * v.x % P;
        return *this;
    }
    friend mint operator+(mint u, mint v) {
        return u += v;
    }
    friend mint operator-(mint u, mint v) {
        return u -= v;
    }
    friend mint operator*(mint u, mint v) {
        return u *= v;
    }
    mint inv() const {
        return power(*this, -1);
    }
    mint pow(i64 v) const {
        if ((v %= P - 1) < 0) 
            v += P - 1;
        return power(*this, v);
    }
    friend istream& operator>>(istream& cin, mint& u) {
        int x;
        cin >> x;
        u = mint(x);
        return cin;
    }
    friend ostream& operator<<(ostream& cout, mint u) {
        return cout << u.x;
    }
};

template<int P>
mint<P> findPrimitiveRoot() {
    mint<P> i = 2;
    int k = __builtin_ctz(P - 1);
    while (true) {
        if (power(i, (P - 1) / 2).x != 1) {
            break;
        }
        i += 1;
    }
    return power(i, (P - 1) >> k);
}

i64 get_len(i64 n) { // if n=0, boom
    return --n, n |= n >> 1, n |= n >> 2, n |= n >> 4, n |= n >> 8, n |= n >> 16, n |= n >> 32, ++n;
}

template <int P> struct NTT {
    using Z = mint<P>;

    inline static vector<Z> r = vector<Z>(1 << 20), ir = vector<Z>(1 << 20);
 
    NTT() = delete;
    static void idft(int n, vector<Z>& x) {
        for (int i = 2; i < n; i <<= 1) {
            for (int j = 0, l = i >> 1; j != l; ++j) {
                Z u = x[j], v = x[j + l];
                x[j] = u + v, x[j + l] = u - v;
            }
 
            for (int j = i, l = i >> 1, m = 1; j != n; j += i, ++m) {
                Z r = ir[m];
 
                for (int k = 0; k != l; ++k) {
                    Z u = x[j + k], v = x[j + k + l];
                    x[j + k] = u + v, x[j + k + l] = (u - v) * r;
                }
            }
        }
 
        Z iv(P - (P - 1) / n);
 
        for (int j = 0, l = n >> 1; j != l; ++j) {
            Z u = x[j] * iv, v = x[j + l] * iv;
            x[j] = u + v, x[j + l] = u - v;
        }
    }
    static void dft(int n, vector<Z>& x) {
        static int lim = 0;
        static const Z G = findPrimitiveRoot<P>();
 
        if (lim == 0) {
            r[1 << 19] = G.pow(P - 1 >> 21), ir[1 << 19] = G.pow(-int(P - 1 >> 21));
 
            for (int i = 18; i != -1; --i)
                r[1 << i] = r[1 << i + 1] * r[1 << i + 1],
                               ir[1 << i] = ir[1 << i + 1] * ir[1 << i + 1];
 
            lim = 1;
        }
 
        while ((lim << 1) < n) {
            for (int i = lim + 1, e = lim << 1; i < e; ++i)
                r[i] = r[i - lim] * r[lim], ir[i] = ir[i - lim] * ir[lim];
 
            lim <<= 1;
        }
 
        for (int j = 0, l = n >> 1; j != l; ++j) {
            Z u = x[j], v = x[j + l];
            x[j] = u + v, x[j + l] = u - v;
        }
 
        for (int i = n >> 1; i >= 2; i >>= 1) {
            for (int j = 0, l = i >> 1; j != l; ++j) {
                Z u = x[j], v = x[j + l];
                x[j] = u + v, x[j + l] = u - v;
            }
 
            for (int j = i, l = i >> 1, m = 1; j != n; j += i, ++m) {
                Z root = r[m];
 
                for (int k = 0; k != l; ++k) {
                    Z u = x[j + k], v = x[j + k + l] * root;
                    x[j + k] = u + v, x[j + k + l] = u - v;
                }
            }
        }
    }
};
 
template <int P> void dft(int n, vector<mint<P>>& x) {
    NTT<P>::dft(n, x);
}
 
template <int P> void idft(int n, vector<mint<P>>& x) {
    NTT<P>::idft(n, x);
}

template <int P>
vector<mint<P>> mul(const vector<mint<P>> &x, const vector<mint<P>> &y) {
    using Z = mint<P>;
    static vector<Z> a = vector<Z>(1 << 21), b = vector<Z>(1 << 21);
    vector<Z> res(x.size() + y.size() - 1);
 
    if (min(x.size(), y.size()) <= 8) {
        int n = x.size(), m = y.size();
        fill(res.begin(), res.end(), 0);
 
        for (int i = 0; i != n; ++i)
            for (int j = 0; j != m; ++j)
                res[i + j] += x[i] * y[j];
    } else {
        copy(x.begin(), x.end(), a.begin());
        copy(y.begin(), y.end(), b.begin());
        int old_size = res.size(), len = get_len(old_size);
        fill(a.begin() + x.size(), a.begin() + len, 0);
        fill(b.begin() + y.size(), b.begin() + len, 0);
        dft(len, a), dft(len, b);
        res.resize(len);
 
        for (int i = 0; i != len; ++i)
            res[i] = a[i] * b[i];
 
        idft(len, res);
        res.resize(old_size);
    }
 
    return res;
}

template <int P>
vector<mint<P>> operator*(const vector<mint<P>> &x, const vector<mint<P>> &y) {
    return mul(x, y);
}