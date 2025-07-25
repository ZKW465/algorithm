using i128 = __int128_t;

// Returns [gcd, x, y] where ax + by = gcd(a,b)
// Type-safe: result matches input type
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


/**
 * Solves ax + by = res
 * Requirement: gcd(a,b) must divide res
 * Returns: [gcd, x, y] with scaled solution
 */
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

/**
 * Solves ax ≡ b (mod P) for minimal x
 * Requirement: gcd(a,P) must divide b
 */
template<typename T>
T lce(T a, T b, T p) {
  auto [g, x, y] = safe_exgcd(a, p, b);
  T t = p / g;
  return norm(x % t, t);
}


/**
 * Computes modular inverse: ax ≡ 1 (mod n)
 * Requirement: gcd(a,n) = 1
 */
template<typename T>
T inv(T a, T p) {
  auto [g, x, y] = exgcd(a, p);
  return norm(x % p, p);
}