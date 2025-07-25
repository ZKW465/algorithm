template <typename T, int N, int M = N> 
struct mat {
  std::array<std::array<T, M>, N> a;

  mat() : a{} {}
  mat(T val) {
    for (auto &i : a)
      i.fill(val);
  }

  static mat eye() {
    static_assert(N == M, "Eye matrix must be square");
    mat res;
    for (int i = 0; i < N; ++i)
      res[i][i] = 1;
    return res;
  }

  auto &operator[](int i) { return a[i]; }
  const auto &operator[](int i) const { return a[i]; }

  mat operator+(const mat &o) const {
    mat res;
    for (int i = 0; i < N; ++i)
      for (int j = 0; j < M; ++j)
        res[i][j] = a[i][j] + o[i][j];
    return res;
  }

  mat operator-(const mat &o) const {
    mat res;
    for (int i = 0; i < N; ++i)
      for (int j = 0; j < M; ++j)
        res[i][j] = a[i][j] - o[i][j];
    return res;
  }

  template <int P> 
  mat<T, N, P> operator*(const mat<T, M, P> &o) const {
    mat<T, N, P> res;
    for (int i = 0; i < N; ++i)
      for (int k = 0; k < M; ++k) {
        T mul = a[i][k];
        for (int j = 0; j < P; ++j)
          res[i][j] += mul * o[k][j];
      }
    return res;
  }

  mat operator*(T x) const {
    mat res;
    for (int i = 0; i < N; ++i)
      for (int j = 0; j < M; ++j)
        res[i][j] = a[i][j] * x;
    return res;
  }

  mat &operator+=(const mat &o) { return *this = *this + o; }
  mat &operator-=(const mat &o) { return *this = *this - o; }
  template <int P> 
  mat &operator*=(const mat<T, M, P> &o) {
    return *this = *this * o;
  }
  mat &operator*=(T x) { return *this = *this * x; }

  mat pow(i64 k) const {
    static_assert(N == M, "Pow only for square matrices");
    mat res = eye(), b = *this;
    for (; k; k >>= 1, b *= b)
      if (k & 1)
        res *= b;
    return res;
  }

  mat<T, M, N> t() const {
    mat<T, M, N> res;
    for (int i = 0; i < N; ++i)
      for (int j = 0; j < M; ++j)
        res[j][i] = a[i][j];
    return res;
  }

  mat inv() const {
    static_assert(N == M, "Inv only for square matrices");
    mat<T, N, 2 * N> aug;
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j)
        aug[i][j] = a[i][j];
      aug[i][i + N] = 1;
    }
    for (int i = 0; i < N; ++i) {
      int p = i;
      while (p < N && aug[p][i] == 0)
        ++p;
      if (p == N)
        return mat();
      if (p != i)
        std::swap(aug[i], aug[p]);
      T inv = 1 / aug[i][i];
      for (int j = i; j < 2 * N; ++j)
        aug[i][j] *= inv;
      for (int k = 0; k < N; ++k) {
        if (k == i || aug[k][i] == 0)
          continue;
        T f = aug[k][i];
        for (int j = i; j < 2 * N; ++j)
          aug[k][j] -= f * aug[i][j];
      }
    }
    mat res;
    for (int i = 0; i < N; ++i)
      for (int j = 0; j < N; ++j)
        res[i][j] = aug[i][j + N];
    return res;
  }
};