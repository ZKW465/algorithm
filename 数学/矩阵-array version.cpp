template <typename T, size_t N, size_t M = N> 
struct Mat {
  std::array<std::array<T, M>, N> a;

  Mat() {
    for (auto &row : a)
      row.fill(0);
  }
  Mat(T val) {
    for (auto &row : a)
      row.fill(val);
  }

  static Mat eye() {
    static_assert(N == M, "Eye matrix must be square");
    Mat res;
    for (size_t i = 0; i < N; ++i)
      res[i][i] = 1;
    return res;
  }

  auto &operator[](size_t i) { return a[i]; }
  const auto &operator[](size_t i) const { return a[i]; }

  Mat operator+(const Mat &o) const {
    Mat res;
    for (size_t i = 0; i < N; ++i)
      for (size_t j = 0; j < M; ++j)
        res[i][j] = a[i][j] + o[i][j];
    return res;
  }

  Mat operator-(const Mat &o) const {
    Mat res;
    for (size_t i = 0; i < N; ++i)
      for (size_t j = 0; j < M; ++j)
        res[i][j] = a[i][j] - o[i][j];
    return res;
  }

  template <size_t P> Mat<T, N, P> operator*(const Mat<T, M, P> &o) const {
    Mat<T, N, P> res;
    for (size_t i = 0; i < N; ++i)
      for (size_t j = 0; j < P; ++j)
        for (size_t k = 0; k < M; ++k)
          res[i][j] += a[i][k] * o[k][j];
    return res;
  }

  Mat operator*(T x) const {
    Mat res;
    for (size_t i = 0; i < N; ++i)
      for (size_t j = 0; j < M; ++j)
        res[i][j] = a[i][j] * x;
    return res;
  }

  Mat &operator+=(const Mat &o) { return *this = *this + o; }
  Mat &operator-=(const Mat &o) { return *this = *this - o; }
  template <size_t P> Mat &operator*=(const Mat<T, M, P> &o) {
    return *this = *this * o;
  }
  Mat &operator*=(T x) { return *this = *this * x; }

  Mat pow(uint64_t k) const {
    static_assert(N == M, "Pow only for square matrices");
    Mat res = eye(), b = *this;
    for (; k; k >>= 1, b *= b)
      if (k & 1)
        res *= b;
    return res;
  }

  Mat<T, M, N> t() const {
    Mat<T, M, N> res;
    for (size_t i = 0; i < N; ++i)
      for (size_t j = 0; j < M; ++j)
        res[j][i] = a[i][j];
    return res;
  }

  Mat inv() const {
    static_assert(N == M, "Inv only for square matrices");
    Mat<T, N, 2 * N> aug;
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < N; ++j)
        aug[i][j] = a[i][j];
      aug[i][i + N] = 1;
    }
    for (size_t i = 0; i < N; ++i) {
      size_t p = i;
      while (p < N && aug[p][i] == 0)
        ++p;
      if (p == N)
        return Mat();
      if (p != i)
        std::swap(aug[i], aug[p]);
      T inv = 1 / aug[i][i];
      for (size_t j = i; j < 2 * N; ++j)
        aug[i][j] *= inv;
      for (size_t k = 0; k < N; ++k) {
        if (k == i || aug[k][i] == 0)
          continue;
        T f = aug[k][i];
        for (size_t j = i; j < 2 * N; ++j)
          aug[k][j] -= f * aug[i][j];
      }
    }
    Mat res;
    for (size_t i = 0; i < N; ++i)
      for (size_t j = 0; j < N; ++j)
        res[i][j] = aug[i][j + N];
    return res;
  }
};
