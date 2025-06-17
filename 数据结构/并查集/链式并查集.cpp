struct DSU {
  std::vector<int> l, r;
  DSU() {}
  DSU(int n) { init(n); }
  void init(int n) {
      l.resize(n);
      r.resize(n);
      std::iota(l.begin(), l.end(), 0);
      std::iota(r.begin(), r.end(), 0);
  }

  int next(int x) {
      int t = x;
      while (r[x] != x) {
          x = r[x];
      }
      while (t != x) {
          r[t] = x;
          t = r[t];
      }
      return x;
  }
  int prev(int x) {
      int t = x;
      while (l[x] != x) {
          x = l[x];
      }
      while (t != x) {
          l[t] = x;
          t = l[t];
      }
      return x;
  }
  void remove(int x) {
      r[x] = next(x + 1);
      l[x] = prev(x - 1);
  }
};
