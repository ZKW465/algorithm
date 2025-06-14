int mul(int a, int b, int P) {
  return 1LL * a * b % P;
}

template<typename T>
T power(T a, i64 b, i64 P) {
  T res = 1;
  for (; b; b >>= 1) {
    if (b & 1) {
      res = 1LL * res * a % P;
    }
    a = 1LL * a * a % P;
  }
  return res;
}

int sum2(int a) {
  return 1LL * a * (a + 1) * (2LL * a + 1) / 6;
}