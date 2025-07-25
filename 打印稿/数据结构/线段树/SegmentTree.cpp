template<class Info>
class SegmentTreeTemplate {
public:
  SegmentTreeTemplate() : n(0) {}
  SegmentTreeTemplate(int n_, Info v_ = Info()) {
    init(n_, v_);
  }
  template<class T>
  SegmentTreeTemplate(std::vector<T> init_) {
    init(init_);
  }

  template<typename... Args>
  void modify(int p, Args&&... args) {
    assert(0 <= p && p < n);
    modify2(1, 0, n, p, std::forward<Args>(args)...);
  }

  Info rangeQuery(int l, int r) {
    assert(0 <= l && l < r && r <= n);
    return rangeQuery(1, 0, n, l, r);
  }

  template<class F>
  int findFirst(int l, int r, F pred) {
    return findFirst(1, 0, n, l, r, pred);
  }

  template<class F>
  int findLast(int l, int r, F pred) {
    return findLast(1, 0, n, l, r, pred);
  }

  std::string to_string(int l = 0, int r = -1) {
    if (r == -1) r = n;
    return to_string(1, 0, n, l, r);
  }

private:
  int n;
  std::vector<Info> info;

  void init(int n_, Info v_ = Info()) {
    init(std::vector(n_, v_));
  }
  template<class T>
  void init(std::vector<T> init_) {
    n = init_.size();
    info.assign(4 << std::__lg(n), Info());
    std::function<void(int, int, int)> build = [&](int p, int l, int r) {
      if (r - l == 1) {
        info[p] = init_[l];
        return;
      }
      int m = (l + r) / 2;
      build(2 * p, l, m);
      build(2 * p + 1, m, r);
      pull(p, l, m, r);
    };
    build(1, 0, n);
  }

  void pull(int p, int l, int m, int r) {
    info[p].update(info[2 * p], info[2 * p + 1], l, m, r);
  }

  template<typename... Args>
  void modify2(int p, int l, int r, int x, Args&&... args) {
    if (r - l == 1) {
      info[p].apply(std::forward<Args>(args)..., l, r);
      return;
    }
    int m = (l + r) / 2;
    if (x < m) {
      modify2(2 * p, l, m, x, std::forward<Args>(args)...);
    } else {
      modify2(2 * p + 1, m, r, x, std::forward<Args>(args)...);
    }
    pull(p, l, m, r);
  }
  
  Info rangeQuery(int p, int l, int r, int x, int y) {
    if (l >= x && r <= y) {
      return info[p];
    }
    int m = (l + r) / 2;
    if (m >= y) {
      return rangeQuery(2 * p, l, m, x, y);
    } else if (m <= x) {
      return rangeQuery(2 * p + 1, m, r, x, y);
    } else {
      return Info::merge(
        rangeQuery(2 * p, l, m, x, y), 
        rangeQuery(2 * p + 1, m, r, x, y), 
        std::max(l, x), m, std::min(r, y)
      );
    }
  }

  template<class F>
  int findFirst(int p, int l, int r, int x, int y, F pred) {
    if (l >= y || r <= x || !pred(info[p])) {
      return -1;
    }
    if (r - l == 1) {
      return l;
    }
    int m = (l + r) / 2;
    int res = findFirst(2 * p, l, m, x, y, pred);
    if (res == -1) {
      res = findFirst(2 * p + 1, m, r, x, y, pred);
    }
    return res;
  }
  
  template<class F>
  int findLast(int p, int l, int r, int x, int y, F pred) {
    if (l >= y || r <= x || !pred(info[p])) {
      return -1;
    }
    if (r - l == 1) {
      return l;
    }
    int m = (l + r) / 2;
    int res = findLast(2 * p + 1, m, r, x, y, pred);
    if (res == -1) {
      res = findLast(2 * p, l, m, x, y, pred);
    }
    return res;
  }
  
  std::string to_string(int p, int l, int r, int x, int y, int dep = 0) {
    if (l >= y || r <= x) {
      return {};
    }
    int m = (l + r) >> 1;
    std::stringstream ss;
    if (r - l > 1) {
      ss << to_string(p * 2, l, m, x, y, dep + 1);
    }
    ss << string(dep, '\t');
    ss << "(" << l << ", " << r << "), " << info[p];
    ss << '\n';
    if (r - l > 1) {
      ss << to_string(p * 2 + 1, m, r, x, y, dep + 1);
    }
    return ss.str();
  }

  friend ostream &operator<<(ostream &cout, SegmentTreeTemplate u) {
    return cout << u.to_string();
  }
};

struct Info {
  Info() = default;
  void apply(int add, int l, int r) {}
  void update(const Info &u, const Info &v, int l, int m, int r) {}
  static Info merge(const Info &u, const Info &v, int l, int m, int r) {
    Info info = Info();
    info.update(u, v, l, m, r);
    return info;
  }
  friend ostream &operator<<(ostream &cout, Info t) {
    return cout << "{" << "}";
  }
};

using SegmentTree = SegmentTreeTemplate<Info>;