constexpr int kBufSize = 1 << 20;

struct Input {
  char buf[kBufSize];
  char *p1 = buf;
  char *p2 = buf;

  __attribute__((always_inline)) char gc() {
    if (__builtin_expect(p1 == p2, 0)) {
      p2 = (p1 = buf) + fread(buf, 1, kBufSize, stdin);
      if (__builtin_expect(p1 == p2, 0)) return EOF;
    }
    return *p1++;
  }
  
  __attribute__((always_inline)) bool isdigit(char c) { 
    return c >= '0' && c <= '9'; 
  }
  
  __attribute__((always_inline)) bool blank(char c) {
    return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == EOF;
  }

  void tie(void*) {}

  template<typename T>
  requires is_integral_v<T>
  Input& operator>>(T& x) {
    x = 0;
    bool neg = false;
    char ch = gc();
    for (; !isdigit(ch); ch = gc())
      if (ch == '-')
        neg = true;
    for (; isdigit(ch); ch = gc())
      x = (x << 3) + (x << 1) + (ch ^ 48);
    if (neg)
      x = -x;
    return *this;
  }
  Input& operator>>(char& x) {
    x = gc();
    for (; blank(x); x = gc());
    return *this;
  }
  Input& operator>>(double& x) {
    x = 0;
    double tmp = 1;
    bool neg = 0;
    char ch = gc();
    for (; !isdigit(ch); ch = gc())
      if (ch == '-')
        neg = 1;
    for (; isdigit(ch); ch = gc())
      x = x * 10 + ch - '0';
    if (ch == '.')
      for (ch = gc(); isdigit(ch); ch = gc())
        tmp /= 10.0, x += tmp *(ch - '0');
    if (neg) 
      x = -x;
    return *this;
  }
  Input& operator>>(string& s) {
    s.clear();
    char ch = gc();
    while (blank(ch)) ch = gc();
    for (; !blank(ch); ch = gc())
      s += ch;
    return *this;
  }
} input;
# define cin input

struct Output {
  char pbuf[kBufSize];
  char *pp = pbuf;
  char stk[40];
  int top = 0;

  __attribute__((always_inline)) void push(char c) {
    if (__builtin_expect(pp - pbuf == kBufSize, 0)) {
      fwrite(pbuf, 1, kBufSize, stdout);
      pp = pbuf;
    }
    *pp++ = c;
  }

  ~Output() { fwrite(pbuf, 1, pp - pbuf, stdout); }

  template<class T>
  requires is_integral_v<T>
  Output& operator<<(T x) {
    if (x < 0) {
      push('-');
      x = -x;
    }
    do {
      stk[++top] = '0' + x % 10;
      x /= 10;
    } while (x);
    while (top) {
      push(stk[top--]);
    }
    return *this;
  }

  template<typename T>
  typename std::enable_if<std::is_same<T, double>::value, Output&>::type
  operator<<(const T&) = delete; // 不能输出double，因为4舍5入问题

  Output& operator<<(const string& x) {
    for (char u : x) {
      push(u);
    }
    return *this;
  }
  template<size_t N>
  Output& operator<<(const char(&x)[N]) {
    *this << string(x);
    return *this;
  }
  Output& operator<<(const char* const& x) {
    for (const char* ptr = x; *ptr != '\0'; ++ptr) {
      push(*ptr);
    }
    return *this;
  }
  Output& operator<<(char x) {
    push(x);
    return *this;
  }
  Output& operator<<(bool x) {
    push(x ? '1' : '0');
    return *this;
  }
} output;
# define cout output