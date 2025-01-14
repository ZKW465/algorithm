template<typename T>
T power(T x, i64 b) {
    T res {1};
    for (; b; b >>= 1, x *= x) {
        if (b & 1) {
            res *= x;
        }
    }
    return res;
}

struct Z {
    static constexpr int P = 998244353;
    int x = 0;
    Z() {}
    Z(i64 x) : x(norm(x % P)) {}
    int norm(int x) {
        if (x >= P) x -= P;
        if (x < 0) x += P;
        return x;
    }
    Z operator-() {
        return -x;
    }
    Z &operator+=(Z v) {
        x = norm(x + v.x);
        return *this;
    }
    Z &operator-=(Z v) {
        x = norm(x - v.x);
        return *this;
    }
    Z &operator*=(Z v) {
        x = 1ll * x * v.x % P;
        return *this;
    }
    Z &operator/=(Z v) {
        return *this *= v.inv();
    }
    Z inv() {
        return power(*this, P - 2);
    }
    friend Z operator+(Z u, Z v) {
        return u += v;
    }
    friend Z operator-(Z u, Z v) {
        return u -= v;
    }
    friend Z operator*(Z u, Z v) {
        return u *= v;
    }
    friend Z operator/(Z u, Z v) {
        return u /= v;
    }
    friend istream &operator>>(istream &cin, Z &v) {
        i64 x;
        cin >> x;
        v = x;
        return cin;
    }
    friend ostream &operator<<(ostream &cout, Z v) {
        return cout << v.x;
    }
};  