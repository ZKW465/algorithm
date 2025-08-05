class SegmentTree {
 public:
  SegmentTree() {}

  void reserve(int n) {
    line.reserve(2 * n), pos.reserve(2 * n);
  }
  
  // 左下和右上 在笛卡尔坐标系中
  void addRectangle(int x, int l, int y, int r) {
    line.emplace_back(x, l, r, 1);
    line.emplace_back(y, l, r, -1);
    pos.push_back(l);
    pos.push_back(r);
  }

  void addRange(int x, int y, int l, int r) {
    addRectangle(x, l, y + 1, r + 1);
  }

  i64 answer() {
    if (line.empty()) {
      return 0LL;
    }

    int n = line.size();
    i64 ans = 0;

    sort(line.begin(), line.end());
    sort(pos.begin(), pos.end());
    int m = unique(pos.begin(), pos.end()) - pos.begin();
    len.assign(8 * m, 0);
    tag.assign(8 * m, 0);

    for (int i = 0; i < n - 1; i += 1) {
      modify(1, 0, m - 2, line[i].l, line[i].r, line[i].add);
      ans += 1LL * len[1] * (line[i + 1].h - line[i].h);
    }
    return ans;
  }
 private:
  struct Line {
    int h, l, r, add;
    friend bool operator<(const Line &u, const Line &v) {
      return u.h < v.h;
    }
  };
  vector<Line> line;
  vector<int> pos, len, tag;

  void pull(int p, int l, int r) {
    if (tag[p]) len[p] = pos[r + 1] - pos[l];
    else len[p] = len[p << 1] + len[p << 1 | 1];
  }

  void modify(int p, int l, int r, int x, int y, int v) {
    if (x <= pos[l] && pos[r + 1] <= y) {
      tag[p] += v;
      pull(p, l, r);
      return;
    }
    int m = l + r >> 1;
    if (x <= pos[m])
      modify(p << 1, l, m, x, y, v);
    if (pos[m + 1] < y)
      modify(p << 1 | 1, m + 1, r, x, y, v);
    pull(p, l, r);
  }
};