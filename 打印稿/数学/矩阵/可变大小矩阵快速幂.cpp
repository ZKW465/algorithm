constexpr int N = 100;

struct mat {
  inline static int n = N;
  array<array<Z, N>, N> a{};
  static mat eye() {
    mat u;
    for (int i = 0; i < n; i += 1) {
      u.a[i][i] = 1;
    }
    return u;
  }
  static void set_lim(int n_) {
    n = n_;
  }
  void clean() {
    for (int i = 0; i < n; i += 1) {
      for (int j = 0; j < n; j += 1) {
        a[i][j] = 0;
      }
    }
  }
  void copy(const mat& v) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        a[i][j] = v.a[i][j];
      }
    }
  }
  void turn_eye() {
    clean();
    for (int i = 0; i < n; i += 1) {
      a[i][i] = 1;
    }
  }
  void cycle_shift(int c) {
    turn_eye();
    for (int i = 0; i < n; i += 1) {
      a[(n + i - c) % n][i] += 1;
    }
  }
  friend mat operator*(const mat &u, const mat &v) {
    mat z;
    for (int i = 0; i < n; i += 1) {
      for (int k = 0; k < n; k += 1) {
        Z mul = u.a[i][k];
        for (int j = 0; j < n; j += 1) {
          z.a[i][j] += mul * v.a[k][j];
        }
      }
    }
    return z;
  }
  mat &operator*=(const mat &v) {
    this->copy(*this * v);
    return *this;
  }
  mat pow(i64 b) {
    mat a = *this;
    mat res;
    res.turn_eye();
    for (; b; b /= 2, a *= a) {
      if (b & 1) {
        res *= a;
      }
    }
    return res;
  }
};