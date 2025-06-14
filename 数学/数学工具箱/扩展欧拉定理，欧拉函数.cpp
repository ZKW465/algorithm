int power(int a, int b, int P) {
  int res = 1;
  for (; b; b >>= 1) {
    if (b & 1) {
      res = 1LL * res * a % P;
    }
    a = 1LL * a * a % P;
  }
  return res;
}

/**
 * Computes Euler's totient function φ(n)
 * Counts integers < n coprime with n
 * Time: O(√n)
 */
int phi(int n) {
  int res = n;
  for (int i = 2; i * i <= n; i++)
    if (n % i == 0) {
      res = res / i * (i - 1);
      while (n % i == 0) {
        n /= i;
      }
    }
  if (n > 1) {
    res = res / n * (n - 1);
  }
  return res;
}

/**
 * Extended Euler's theorem for modular exponentiation
 * Efficiently computes a^b mod P for very large b
 * Handles cases where a and P are not coprime
 * Time: O(√P) (due to phi calculation)
 */

int expow(int a, i64 b, int P) {
  int p = phi(P); // if P is a prime, then p = P - 1;
  if (b >= p) {
    b %= p;
    if (std::__gcd(a, P) != 1) {
      b += p;
    }
  }
  return power(a, b, P);
}