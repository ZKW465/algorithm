template<class T>
struct Comb {
    inline constexpr static int P = T::mod();

    int n;
    std::vector <T> _fac;
    std::vector <T> _invfac;
    std::vector <T> _inv;

    Comb() : n{0}, _fac{1}, _invfac{1}, _inv{0} {}

    Comb(int n) : Comb() {
        init(n);
    }

    void init(int m) {
        m = std::min(m, P - 1);
        if (m <= n) return;
        _fac.resize(m + 1);
        _invfac.resize(m + 1);
        _inv.resize(m + 1);

        for (int i = n + 1; i <= m; i++) {
            _fac[i] = _fac[i - 1] * i;
        }
        _invfac[m] = _fac[m].inv();
        for (int i = m; i > n; i--) {
            _invfac[i - 1] = _invfac[i] * i;
            _inv[i] = _invfac[i] * _fac[i - 1];
        }
        n = m;
    }

    T fac(int m) {
        if (m > n) init(2 * m);
        return _fac[m];
    }

    T invfac(int m) {
        if (m > n) init(2 * m);
        return _invfac[m];
    }

    T inv(int m) {
        if (m > n) init(2 * m);
        return _inv[m];
    }

    /**
     * @brief 计算组合数 C(n, m)
     */
    T binom(int n, int m) {
        if (n < m || m < 0) return 0;
        return fac(n) * invfac(m) * invfac(n - m);
    }

    /**
     * @brief 第二类斯特林数 S(n, m)
     * 时间复杂度: O(m log m)
     */
    T stirling_second(int n, int m) {
        T ans = 0;
        for (int i = 0; i <= m; ++i) {
            ans += (((m - i) & 1) == 1 ? -1 : 1) * power(T(i), n) * invfac(i) * invfac(m - i);
        }
        return ans;
    }

    /**
     * @brief 卡特兰数 C_n
     */
    T catalan(int n) {
        return binom(2 * n, n) * inv(n + 1);
    }

    /**
     * @brief 卢卡斯定理计算大组合数
     * @note 适用于模数P较小的情况
     */
    T lucas(i64 n, i64 m) {
        if (m == 0) return T(1);
        return binom(n % P, m % P) * lucas(n / P, m / P);
    }
};

Comb<Z> comb;