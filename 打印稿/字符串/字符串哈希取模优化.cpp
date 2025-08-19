mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

bool isprime(int n) {
  if (n <= 1) {
    return false;
  }
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}

int findPrime(int n) {
  while (!isprime(n)) {
    n++;
  }
  return n;
}

using u32 = uint32_t;
using u64 = uint64_t;
using u128 = __uint128_t;

class Barrett {
 public:
  Barrett() = default;
  Barrett(u32 m_) : m(m_), im((u64)(-1) / m_ + 1) {}

  int mod() const {
    return m;
  }

  int add(int a, int b) {
    a += b;
    if (a >= m) {
      a -= m;
    }
    return a;
  }

  int sub(int a, int b) {
    a -= b;
    if (a < 0) {
      a += m;
    }
    return a;
  }

  int mul(u32 a, u32 b) const {
    u64 z = a;
    z *= b;
    
    u64 x = u64((u128(z) * im) >> 64);
    
    u32 v = u32(z - x * m);
    if (m <= v) {
      v += m;
    }
    return v;
  }
 
 private:
  u32 m;
  u64 im;
};

template<int N>
class StringHash {
 public:
  StringHash() = default;

  StringHash(const string &s) {
    int n = s.size();
    p.resize(n);
    h.resize(n);
    p[0].fill(1);
    h[0].fill(1);
    for (int j = 0; j < N; j++) {
      assert(s[0] < mod[j].mod());
      h[0][j] = s[0];
      p[0][j] = 1;
    }
    for (int i = 1; i < n; i++) {
      for (int j = 0; j < N; j++) {
        p[i][j] = mod[j].mul(p[i - 1][j], base[j]);
        h[i][j] = mod[j].add(mod[j].mul(h[i - 1][j], base[j]), s[i]);
      }
    }
  }
  array<int, N> query(int l, int r) {
    if (l > r) {
      return array<int, N>{};
    }
    if (l == 0) {
      return h[r];
    }
    array<int, N> ans{};
    for (int i = 0; i < N; i++) {
      ans[i] = mod[i].sub(h[r][i], mod[i].mul(h[l - 1][i], p[r - l + 1][i]));
    }
    return ans;
  }
 private:
  static array<Barrett, N> mod;
  static array<int, N> base;
  vector<array<int, N>> p, h;
};

constexpr int HN = 2;
template<int N>
array<Barrett, N> StringHash<N>::mod = []() {
  array<Barrett, N> res{};
  for (int i = 0; i < N; i++) {
    res[i] = Barrett(findPrime(rng() % 900'000'000 + 100'000'000));
  }
  return res;
}();

template<int N>
array<int, N> StringHash<N>::base = []() {
  array<int, N> res;
  for (int i = 0; i < N; i++) {
    int c = 1;
    for (int j = 0; j < 2 * i + 1; j++) {
      c = c * 10 + 3;
    }
    c = c * 10 + 1;
    res[i] = c;
  }
  return res;
}();

using Hashing = StringHash<HN>;