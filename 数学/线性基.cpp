/* bitmask set
  T in  [0, 32]  use u32
        [33,64]  use u64
        [65 128] use u128
*/
template<int N, typename T = int>
struct bmset {
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
  bool check(T x) {
    for (int i = N - 1; i >= 0; i--)
      if (x >> i & 1) {
        if (!a[i]) {
          break;
        }
        x ^= a[i];
      }
    return x == 0;
  }
  T max(T res) {
    for (int i = N - 1; i >= 0; i--)
      if ((res ^ a[i]) > res)
        res ^= a[i];
    return res;
  }
  T min(T res) {
    for (int i = N - 1; i >= 0; i--)
      if (res >> i & 1)
        res ^= a[i];
    return res;
  }
  T kth(int k) {
    array<T, N> t{};
    int n = 0;
    T res = 0;
    for (int i = 0; i < N; i++) {
      for (int j = i - 1; j >= 0; j--)
        if (a[i] >> j & 1)
          a[i] ^= a[j];
      if (a[i]) t[n++] = a[i];
    }
    for (int i = 0; i < n; i++)
      if (k >> i & 1) 
        res ^= t[i];
    return res;
  }
  void merge(bmset& v) {
    for (int i = 0; i < N; i++)
      insert(v.a[i]);
  }
};