mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

bool isprime(int n) {
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int findPrime(int n) {
    while (!isprime(n)) {
        n++;
    }
    return n;
}

template<int N>
struct StringHash {
    static array<int, N> mod;
    static array<int, N> base;
    vector<array<int, N>> p, h;
    StringHash() = default;

    StringHash(const string& s) {
        int n = s.size();
        p.resize(n);
        h.resize(n);
        p[0].fill(1);
        h[0].fill(1);
        for (int j = 0; j < N; j++) {
            h[0][j] = s[0] % mod[j];
            p[0][j] = 1;
        }
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < N; j++) {
                p[i][j] = 1LL * p[i - 1][j] * base[j] % mod[j];
                h[i][j] = (1LL * h[i - 1][j] * base[j] + s[i]) % mod[j];
            }
        }
    }
    array<int, N> query(int l, int r) {
        if (l > r) {
            return array<int, N>{};
        }
        if (l == 0) {
            return h[r];
        }
        array<int, N> ans{};
        for (int i = 0; i < N; i++) {
            ans[i] = (h[r][i] - 1LL * h[l - 1][i] * p[r - l + 1][i] % mod[i] + mod[i]) % mod[i];
        }
        return ans;
    }
};

constexpr int HN = 2;
template<int N>
array<int, N> StringHash<N>::mod = []() {
    array<int, N> res;
    for (int i = 0; i < N; i++) {
        res[i] = findPrime(rng() % 900'000'000 + 100'000'000);
    }
    return res;
}();

template<int N>
array<int, N> StringHash<N>::base = []() {
    array<int, N> res;
    for (int i = 0; i < N; i++) {
        int c = 1;
        for (int j = 0; j < 2 * i + 1; j++) {
            c = c * 10 + 3;
        }
        c = c * 10 + 1;
        res[i] = c;
    }
    return res;
}();

using Hashing = StringHash<HN>;