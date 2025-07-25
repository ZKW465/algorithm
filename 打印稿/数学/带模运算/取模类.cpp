template<typename T>
T power(T a, int b, T res = 1) {
    for (; b; b >>= 1, a *= a) {
        if (b & 1) {
            res *= a;
        }
    }
    return res;
}

template<int P>
struct mint {
    int x;
    mint(i64 x_ = 0) : x(norm(x_ % P)) {}
    static constexpr int mod() { return P; }
    template<bool U = true>
    static int norm(int x) {
        if constexpr (U) { if (x < 0) x += P; }
        else { if (x >= P) x -= P; }
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
    mint& operator/=(mint v) {
        return *this *= v.inv();
    }
    bool operator==(mint v) const {
        return x == v.x;
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
    friend mint operator/(mint u, mint v) {
        return u /= v;
    }
    mint inv() const {
        return pow(-1);
    }
    mint pow(i64 v) const {
        if ((v %= P - 1) < 0) 
            v += P - 1;
        return power(*this, v);
    }
    template<typename istream>
    friend istream& operator>>(istream& cin, mint& u) {
        int x;
        cin >> x;
        u = mint(x);
        return cin;
    }
    template<typename ostream>
    friend ostream& operator<<(ostream& cout, mint u) {
        return cout << u.x;
    }
};

constexpr int P = 998244353;
using Z = mint<P>;