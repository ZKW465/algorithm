int siz = 0;

struct mat {
    array<array<Z, N>, N> a{};
    void init1() {
        for (int i = 0; i < siz; i += 1) {
            a[i][i] = 1;
        }
    }
    void init(int c) {
        for (int i = 0; i < siz; i += 1) {
            for (int j = 0; j < siz; j += 1) {
                a[i][j] = 0;
            }
        }
        for (int i = 0; i < siz; i += 1) {
            a[i][i] = 1;
        }
        for (int i = 0; i < siz; i += 1) {
            a[(siz + i - c) % siz][i] += 1;
        }
    }
    friend mat operator*(const mat& u, const mat& v) {
        int n = siz;
        mat z;
        for (int k = 0; k < n; k += 1) {
            for (int i = 0; i < n; i += 1) {
                for (int j = 0; j < n; j += 1) {
                    z.a[i][j] += u.a[i][k] * v.a[k][j];
                }
            }
        }
        return z;
    }
    mat& operator*=(const mat& v) {
        *this = *this * v;
        return *this;
    }
};

mat powermat(mat a, i64 b) {
    mat res;
    res.init1();
    for (; b; b /= 2, a *= a) {
        if (b % 2 == 1) {
            res *= a;
        }
    }
    return res;
}