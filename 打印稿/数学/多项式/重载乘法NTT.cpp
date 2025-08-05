template <int P> 
mint<P> findPrimitiveRoot() {
  mint<P> i = 2;
  int k = __builtin_ctz(P - 1);
  while (true) {
    if (power(i, (P - 1) / 2).x != 1) {
      break;
    }
    i += 1;
  }
  return power(i, (P - 1) >> k);
}

int NTTBuf[1 << 21];

template <int P> struct NTT {
  using Z = mint<P>;
  NTT() = delete;

  inline static Z *r = reinterpret_cast<Z *>(NTTBuf),
                  *ir = reinterpret_cast<Z *>(NTTBuf + (1 << 20));

  static void dft(vector<Z> &f, int n) {
    static int lastn = -1;
    static const Z g = findPrimitiveRoot<P>();

    int m = 1 << __lg(n - 1);

    if (m != lastn) {
      lastn = m;
      r[0] = ir[0] = 1;
      for (int i = 1; i < m; i <<= 1) {
        r[i] = g.pow((P - 1 >> 2) / i);
        ir[i] = g.pow(P - 1 - (P - 1 >> 2) / i);
      }
      for (int i = 1; i < m; ++i) {
        r[i] = r[i & (i - 1)] * r[i & -i];
        ir[i] = ir[i & (i - 1)] * ir[i & -i];
      }
    }

    f.resize(n);

    for (int i = n >> 1, l = n; i; i >>= 1, l >>= 1) {
      for (int j = 0, m = 0; j != n; j += l, ++m) {
        for (int k = j; k != j + i; ++k) {
          Z u = f[k], v = f[k + i] * r[m];
          f[k] = u + v, f[k + i] = u - v;
        }
      }
    }
  }

  static void idft(vector<Z> &f, int n) {
    f.resize(n);
    for (int i = 1, l = 2; i < n; i <<= 1, l <<= 1) {
      for (int j = 0, m = 0; j != n; j += l, ++m) {
        for (int k = j; k != j + i; ++k) {
          Z u = f[k], v = -f[k + i];
          f[k] = u - v, f[k + i] = (u + v) * ir[m];
        }
      }
    }
    Z iv = P - (P - 1) / n;
    for (int i = 0; i < n; ++i) {
      f[i] *= iv;
    }
  }
};

template <int P>
vector<mint<P>> operator*(vector<mint<P>> &x, vector<mint<P>> &y) {
  int tot = x.size() + y.size() - 1;
  if (std::min(x.size(), y.size()) <= 8) {
    int n = x.size(), m = y.size();
    vector<mint<P>> res(tot);
    for (int i = 0; i != n; ++i) {
      for (int j = 0; j != m; ++j) {
        res[i + j] += x[i] * y[j];
      }
    }
    return res;
  }
  int n = 1 << __lg(tot - 1) + 1;
  assert(((P - 1) & (n - 1)) == 0);
  NTT<P>::dft(x, n);
  NTT<P>::dft(y, n);
  for (int i = 0; i < n; ++i) {
    x[i] = x[i] * y[i];
  }
  NTT<P>::idft(x, n);
  x.resize(tot);
  return x;
}