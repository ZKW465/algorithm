template <typename T> 
struct Matrix : public vector<vector<T>> {
  using vector<vector<T>>::vector;
  Matrix(int x) : vector<vector<T>>(x, vector<T>(x)) {};
  Matrix(int x, int y) : vector<vector<T>>(x, vector<T>(y)) {};
  Matrix(int x, int y, T c) : vector<vector<T>>(x, vector<T>(y, c)) {};

  void clean() {
    int n = this->size();
    int m = this->back().size();
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        (*this)[i][j] = 0;
      }
    }
  }
  
  void turn_eye() {
    clean();
    int n = this->size();
    for (int i = 0; i < n; i++) {
      (*this)[i][i] = 1;
    }
  }

  Matrix operator+(Matrix a) {
    auto it = *this;
    int n = a.size();
    int m = a.back().size();
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        it[i][j] += a[i][j];
    return it;
  }

  Matrix operator-(Matrix a) {
    auto it = *this;
    int n = a.size();
    int m = a.back().size();
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        it[i][j] -= a[i][j];
    return it;
  }

  Matrix operator*(Matrix a) {
    int n = this->size();
    int mid = a.size();
    int m = a.back().size();
    Matrix<T> it(n, m);
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        for (int k = 0; k < mid; ++k)
          it[i][j] += (*this)[i][k] * a[k][j];
    return it;
  }

  template <typename U, typename V>
  friend Matrix<U> operator*(Matrix<U> x, V a) {
    int n = x.size();
    int m = x.back().size();
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        x[i][j] *= a;
    return x;
  }

  Matrix &operator+=(Matrix a) { return *this = *this + a; }
  Matrix &operator-=(Matrix a) { return *this = *this - a; }
  Matrix &operator*=(Matrix a) { return *this = *this * a; }

  template <typename U, typename V>
  friend Matrix<U> &operator*=(Matrix<U> &x, V a) {
    return x = x * a;
  }

  Matrix pow(i64 b) {
    auto res = Matrix(this->size(), this->size());
    res.turn_eye();
    auto a = *this;
    for (; b; b /= 2, a *= a)
      if (b & 1)
        res *= a;
    return res;
  }
  Matrix Transpose() {
    int n = this->back().size(), m = this->size();
    auto it = Matrix(n, m);
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        it[i][j] = (*this)[j][i];
    return it;
  }
  Matrix inv() {
    int n = this->size();
    Matrix<T> it(n, 2 * n);
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        it[i][j] = (*this)[i][j];
    for (int i = 0; i < n; ++i)
      it[i][i + n] = 1;
    for (int i = 0; i < n; ++i) {
      int r = i;
      for (int k = i; k < n; ++k)
        if (it[k][i] != 0) {
          r = k;
          break;
        }
      if (r != i)
        swap(it[r], it[i]);
      if (it[i][i] == 0)
        return Matrix<T>();

      T x = it[i][i].inv();
      for (int k = 0; k < n; ++k) {
        if (k == i)
          continue;
        T t = it[k][i] * x;
        for (int j = i; j < 2 * n; ++j)
          it[k][j] -= t * it[i][j];
      }
      for (int j = 0; j < 2 * n; ++j)
        it[i][j] *= x;
    }
    Matrix<T> ans(n, n);
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        ans[i][j] = it[i][j + n];
    return ans;
  }
};