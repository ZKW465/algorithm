template<typename Comp>
struct Value { static i64 x; };

template<> i64 Value<std::less<i64>>::x = std::numeric_limits<i64>::max();
template<> i64 Value<std::greater<i64>>::x = std::numeric_limits<i64>::min();

template<typename Comp = std::greater<i64>>
class Segment {
 public:
  Segment(int n) { init(n); }

  void modify(int p, int l, int r, int x, int y, line u) {
    if (r <= x || y <= l) {
      return;
    }
    int m = (l + r) / 2;
    if (x <= l && r <= y) {
      if (comp(u(m), line[p](m))) {
        std::swap(u, line[p]);
      } 
      if (comp(u(l), line[p](l))) {
        modify(p * 2, l, m, x, y, u);
      } 
      if (comp(u(r - 1), line[p](r - 1))) {
        modify(p * 2 + 1, m, r, x, y, u);
      } 
      return;
    }
    modify(p * 2, l, m, x, y, u);
    modify(p * 2 + 1, m, r, x, y, u);
  }

  i64 query(int p, int l, int r, int u) {
    if (r - l == 1) {
      return line[p](u);
    }
    int m = (l + r) / 2;
    i64 res = line[p](u);
    if (u < m) {
      return std::min(res, query(p * 2, l, m, u), comp);
    } else {
      return std::min(res, query(p * 2 + 1, m, r, u), comp);
    }
  }

 private:
  struct Line {
    i64 k, b;
    i64 operator()(int x) { return 1LL * k * x + b; }
  };
  
  Comp comp;
  int n;
  vector<Line> line;
  
  void init(int n_) {
    n = 2 << __lg(n_);
    line.assign(2 * n, {0, Value<Comp>::x});
  }
};