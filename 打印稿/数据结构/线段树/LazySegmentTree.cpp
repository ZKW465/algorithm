template<class Info, class Tag>
class LazySegmentTreeTemplate {
public:
  LazySegmentTreeTemplate() : n(0) {}
  LazySegmentTreeTemplate(int n_, Info v_ = Info()) {
    init(n_, v_);
  }
  template<class T>
  LazySegmentTreeTemplate(std::vector<T> init_) {
    init(init_);
  }
  void modify(int p, const Info &v) {
    modify(1, 0, n, p, v);
  }
  Info rangeQuery(int l, int r) {
    if (l >= r) return Info();
    return rangeQuery(1, 0, n, l, r);
  }
  void rangeApply(int l, int r, const Tag &v) {
    return rangeApply(1, 0, n, l, r, v);
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
  std::vector<Tag> tag;
  void init(int n_, Info v_ = Info()) {
    init(std::vector(n_, v_));
  }
  template<class T>
  void init(std::vector<T> init_) {
    n = init_.size();
    info.assign(n * 4, Info());
    tag.assign(n * 4, Tag());
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
  void apply(int p, const Tag &v, int l, int r) {
    info[p].apply(v, l, r);
    tag[p].apply(v);
  }
  void push(int p, int l, int m, int r) {
    if (bool(tag[p])) {
      apply(2 * p, tag[p], l, m);
      apply(2 * p + 1, tag[p], m, r);
      tag[p] = Tag();
    }
  }
  void modify(int p, int l, int r, int x, const Info &v) {
    if (r - l == 1) {
      info[p] = v;
      return;
    }
    int m = (l + r) / 2;
    push(p, l, m, r);
    if (x < m) {
      modify(2 * p, l, m, x, v);
    } else {
      modify(2 * p + 1, m, r, x, v);
    }
    pull(p, l, m, r);
  }
  Info rangeQuery(int p, int l, int r, int x, int y) {
    if (l >= x && r <= y) {
      return info[p];
    }
    int m = (l + r) / 2;
    push(p, l, m, r);
    if (m >= y) {
      return rangeQuery(2 * p, l, m, x, y);
    } else if (m <= x) {
      return rangeQuery(2 * p + 1, m, r, x, y);
    } else {
      return Info::merge(rangeQuery(2 * p, l, m, x, y), rangeQuery(2 * p + 1, m, r, x, y), l, m, r);
    }
  }
  void rangeApply(int p, int l, int r, int x, int y, const Tag &v) {
    if (l >= y || r <= x) {
      return;
    }
    int m = (l + r) / 2;
    if (l >= x && r <= y) {
      apply(p, v, l, r);
      return;
    }
    push(p, l, m, r);
    rangeApply(2 * p, l, m, x, y, v);
    rangeApply(2 * p + 1, m, r, x, y, v);
    pull(p, l, m, r);
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
    push(p, l, m, r);
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
    push(p, l, m, r);
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
    ss << "(" << l << ", " << r << "), " << info[p] << ", " << tag[p];
    ss << '\n';
    if (r - l > 1) {
      ss << to_string(p * 2 + 1, m, r, x, y, dep + 1);
    }
    return ss.str();
  }
};

struct Tag {
  void apply(Tag t) {}
  operator bool() {
    return true;
  }
  friend ostream &operator<<(ostream &cout, Tag t) {
    return cout << "{" << "}";
  }
};

struct Info {
  void apply(const Tag &t, int l, int r) {}
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

using LazySegmentTree = LazySegmentTreeTemplate<Info, Tag>;