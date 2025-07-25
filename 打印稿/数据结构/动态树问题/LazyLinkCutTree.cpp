template<class Info, class Tag>
struct lazyLinkCutTree {
public:
  lazyLinkCutTree(int n) : n(n) { 
    t.resize(n + 1); 
    t[0].t.set();
    t[0].v.set();
  }
  void splay(int x) {
    up(x);
    while (pos(x)) {
      int y = t[x].p, z = t[y].p;
      if (pos(y))
        ((t[z].r == y) ^ (t[y].r == x))
            ? rotate(x) : rotate(y);
      rotate(x);
    }
    pull(x);
  }

  void expose(int x) {
    for (int y = 0; x;) {
      splay(x);
      t[x].r = y;
      pull(x);
      y = x;
      x = t[x].p;
    }
  }

  void make_root(int x) {
    expose(x);
    splay(x);
    t[x].rev ^= 1;
  }

  auto split(int x, int y) -> const Info& {
    make_root(x);
    expose(y);
    splay(y);
    return t[y].v;
  }

  int find(int x) {
    expose(x);
    splay(x);
    while (t[x].l)
      push(x), x = t[x].l;
    splay(x);
    return x;
  }

  bool link(int x, int y) {
    make_root(x);
    make_root(y);
    if (find(y) != x) {
      t[x].p = y;
      return true;
    }
    return false;
  }

  bool cut(int x, int y) {
    make_root(x);
    if (find(y) == x && t[y].p == x && !t[y].l) {
      t[x].r = t[y].p = 0;
      pull(x);
      return true;
    }
    return false;
  }

  template<typename ...Args>
  void modify(int x, Args ...args) {
    splay(x);
    t[x].v.modify(args...);
    pull(x);
  }

  void lineModify(int x, int y, const Tag& v) {
    split(x, y);
    apply(y, v);
  }
  
  bool connected(int x, int y) {
    make_root(x);
    return find(y) == x;
  }
  void dfs(int u, bool use_push = true) {
#ifndef ONLINE_JUDGE
    cerr << "\nrooted u: " << u << ", P = " << t[u].p << '\n';
    dfs(u, 0, use_push);
#endif
  }
private:
  struct node {
    bool rev;
    int l, r, p;
    Info v;
    Tag t;
  };
  int n;
  vector<node> t;

  bool pos(int x) {
    return t[t[x].p].l == x || t[t[x].p].r == x;
  }

  void pull(int x) {
    t[x].v.up(t[t[x].l].v, t[t[x].r].v);
  }

  void apply(int x, const Tag &v) {
    if (x) {
      t[x].v.apply(v);
      t[x].t.apply(v);
    }
  }

  void push(int x) {
    if (t[x].rev) {
      swap(t[x].l, t[x].r);
      t[t[x].l].v.reverse();
      t[t[x].r].v.reverse();
      t[t[x].r].rev ^= 1;
      t[t[x].l].rev ^= 1;
      t[x].rev = 0;
    }
    if (bool(t[x].t)) {
      apply(t[x].l, t[x].t);
      apply(t[x].r, t[x].t);
      t[x].t.set();
    }
  }

  void up(int x) {
    if (pos(x)) up(t[x].p);
    push(x);
  }

  void rotate(int x) {
    int y = t[x].p, z = t[y].p;
    if (pos(y)) {
      (t[z].r == y ? t[z].r : t[z].l) = x;
    }
    t[x].p = z;
    if (t[y].r == x) {
      t[y].r = t[x].l;
      t[t[x].l].p = y;
      t[x].l = y;
    } else {
      t[y].l = t[x].r;
      t[t[x].r].p = y;
      t[x].r = y;
    }
    t[y].p = x;
    pull(y);
  }

  void dfs(int u, int dep, bool use_push) {
    if (!u) {
      return;
    }
    if (use_push) {
      push(u);
    }
    for (auto i : {0, 1}) {
      if (i == 1) {
        cerr << string(dep, '\t');
        cerr << u << ' ' << t[u].v << ' ' << t[u].t << endl;
      }
      dfs(i ? t[u].r : t[u].l, dep + 1, use_push);
    }
  }
};

struct Tag {
  void apply(const Tag& v) {

  }
  void set() {

  }
  operator bool() {
    return false;
  }
  friend ostream& operator<<(ostream& cout, Tag x) {
    return cout;
  }
};

struct Info {
  void reverse() {
        
  }
  void modify() {

  }
  void up(const Info& u, const Info& v) {

  }
  void apply(const Tag& v) {

  }
  void set() {

  }
  friend ostream& operator<<(ostream& cout, Info x) {
    return cout;
  }
};

using Tree = lazyLinkCutTree<Info, Tag>;