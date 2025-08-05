// [0, n - 1]
template<typename T>
struct SegmentTree {
  vector<T> a; int n; T v;
  SegmentTree(int n, T v = T()) : a(2 * n, v), n(n), v(v) {}

  void Update(int pos, T val) {
    for (a[pos += n] = val; pos > 1; pos /= 2)
      a[pos / 2] = a[pos] + a[pos ^ 1];
  }
  // [b, e)
  T Query(int b, int e) {
    T res = v;
    for (b += n, e += n; b < e; b /= 2, e /= 2) {
      if (b % 2) res = res + a[b++];
      if (e % 2) res = res + a[--e];
    }
    return res;
  }
};