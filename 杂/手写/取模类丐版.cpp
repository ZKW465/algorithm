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
    friend Z operator+(Z u, Z v) {
        return u += v;
    }
    friend Z operator-(Z u, Z v) {
        return u -= v;
    }
    friend Z operator*(Z u, Z v) {
        return u *= v;
    }
};  