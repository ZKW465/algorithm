template <size_t N, 
          typename T = std::conditional_t<N <= 32, uint32_t,
                       std::conditional_t<N <= 64, uint64_t, __uint128_t>>>
requires (1 <= N && N <= 128)
struct BitmastSet {
  array<T, N> a{};

  bool insert(T x) {
    for (int i = N - 1; i >= 0; i--)
      if (x >> i & 1) {
        if (!a[i]) {
          a[i] = x;
          return true;
        }
        x ^= a[i];
      }
    return false;
  }

  bool contains(T x) {
    for (int i = N - 1; i >= 0; i--)
      if (x >> i & 1) {
        if (!a[i]) return false;
        x ^= a[i];
      }
    return true;
  }

  T query_max(T res) {
    for (int i = N - 1; i >= 0; i--) {
      if ((res ^ a[i]) > res) {
        res ^= a[i];
      }
    }
    return res;
  }

  T query_min(T res) {
    for (int i = N - 1; i >= 0; i--) {
      if (res >> i & 1) {
        res ^= a[i];
      }
    }
    return res;
  }

  void normalize() {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < i; j++) {
        if (a[i] >> j & 1) {
          a[i] ^= a[j];
        }
      }
    }
  }

  /**
   * @brief 查询第k小的异或值（必须调用normalize()后使用）
   * @param k 第k小（从0开始计数）
   * @return 第k小的值，如果不存在返回-1
   */
  T kth(T k) {
    T res = 0;
    for (int i = 0; i < N; i++) {
      if (a[i]) {
        if (k & 1) {
          res ^= a[i];
        }
        k /= 2;
      }
    }
    return k ? T(-1) : res;
  }

  void merge(BitmastSet &v) {
    for (int i = 0; i < N; i++) {
      if (v.a[i]) {
        insert(v.a[i]);
      }
    }
  }
};

constexpr int N = 50;
using bmset = BitmastSet<N>;