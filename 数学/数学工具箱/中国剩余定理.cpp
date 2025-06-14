using i128 = __int128_t;

template<typename T>
array<T, 3> exgcd(T a, T b) {
  T x1 = 1, x2 = 0, x3 = 0, x4 = 1;
  while (b != 0) {
    T c = a / b;
    tie(x1, x2, x3, x4, a, b) =
      make_tuple(x3, x4, x1 - x3 * c, 
        x2 - x4 * c, b, a - b * c);
  }
  return {a, x1, x2};
}

template<bool U = true>
auto norm(auto x, auto p) {
  if constexpr (U) {
    if (x < 0) {
      x += p;
    }
  } else {
    if (x >= p) {
      x -= p;
    }
  }
  return x;
}

template<typename T>
T inv(T a, T p) {
  auto [g, x, y] = exgcd(a, p);
  return norm(x % p, p);
}

/**
 * Algorithm: Chinese Remainder Theorem (CRT)
 * Purpose: Solves system of congruences x ≡ a_i (mod p_i)
 * Returns: Solution modulo product of all p_i
 * Requirement: All moduli must be pairwise coprime
 */

template<typename U, typename T, typename V = i128>
U crt(vector<T>& a, vector<T>& p) {
  U n = accumulate(p.begin(), p.end(), U(1), multiplies<U>()), res = 0;

  for (int i = 0; i < a.size(); i++) {
    U m = n / p[i];
    U b = inv<U>(m, p[i]);
    res = norm<false>(res + V(a[i]) * m * b % n, n); // Uses wider type V to prevent overflow
  }
  return res;
}

template<typename U, auto p, typename V = i128>
U crt(auto& a) {
  constexpr int N = p.size();
  static const
  U n = accumulate(p.begin(), p.end(), U(1), multiplies<U>());
  U res = 0;

  static const 
  array<V, N> mul = [&] () {
    array<V, N> res;
    for (int i = 0; i < N; i++) {
      U m = n / p[i];
      res[i] = V(m) * inv<U>(m, p[i]);
    } 
    return res;
  }();
  
  for (int i = 0; i < N; i++) {
    res = norm<false>(res + a[i] * mul[i] % n, n); // Uses wider type V to prevent overflow
  }
  return res;
}

template<typename T>
auto safe_exgcd(T a, T b, T res = 1) {
  auto [g, x, y] = exgcd(a, b);
  assert(res % g == 0);
  if constexpr (is_same<T, int>::value) {
    i64 mul = res / g;
    return make_tuple(g, mul * x, mul * y);
  } else {
    i128 mul = res / g;
    return make_tuple(g, mul * x, mul * y);
  }
}

/**
 * Algorithm: Extended Chinese Remainder Theorem (EXCRT)
 * Purpose: Solves system of congruences x ≡ a_i (mod m_i)
 * Returns: Solution modulo LCM of all m_i
 * Note: Works for non-coprime moduli
 */
template<typename U, typename T, typename V = i128>
U excrt(vector<T> &a, vector<T> &p) {
    U m = p[0], x = a[0];
    for (int i = 1; i < a.size(); i++) {
        T mod = p[i], y = a[i];
        auto [g, z, _] = safe_exgcd<U>(m, mod, y - x);
        V t = V(m) * z + x;
        m = m / g * mod;
        x = norm(t % m, m);
    }
    return x;
}