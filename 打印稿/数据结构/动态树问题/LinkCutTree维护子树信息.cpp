template<class Info>
class linkCutTree {
public:
  // use zero as sentinel
  linkCutTree(int n) : n(n), t(n + 1) { 
    t[0].v.set(); 
  }

  void expose(int x) {
    for (int y = 0; x;) {
      splay(x);
            t[x].v.emplace(t[t[x].r].v);
      t[x].r = y;
            t[x].v.remove(t[t[x].r].v);
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

  // findroot
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
            t[y].v.emplace(t[x].v);
      return true;
    }
    return false;
  }

  bool cut(int x, int y) {
    make_root(x);
    if (find(y) == x
        && t[y].p == x && !t[y].l) {
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

    auto get(int u) -> const Info& {
        return t[u].v;
    }
private:
  struct node {
    bool rev;
    int l, r, p;
    Info v;
  };
  int n;
  vector<node> t;

  // notroot
  bool pos(int x) {
    return t[t[x].p].l == x || t[t[x].p].r == x;
  }

  // splay function 
  void pull(int x) {
    t[x].v.up(t[t[x].l].v, t[t[x].r].v);
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

  void up(int x) {
    if (pos(x)) up(t[x].p);
    push(x);
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

  void dfs(int u, int dep, bool use_push = true) {
    if (!u) {
        return;
    }
    if (use_push) {
      push(u);
    }
    for (auto i : {0, 1}) {
      if (i == 1) {
        cerr << string(dep, '\t');
        cerr << u << ' ' << t[u].v << endl;
      }
      dfs(i ? t[u].r : t[u].l, dep + 1, use_push);
    }
  }
};

struct Info {
  // do reverse info here
  void reverse() {

  }
  // modify info
  void modify() {

  }
    // virtual node memory, push sentinel node into this is Undefined Behavior
    void emplace(const Info& v) {

    }
    // remove virtual node, remove sentinel node into this is Undefined Behavior
    void remove(const Info& v) {

    }
  // merge left and right and yourself
  void up(const Info &u, 
      const Info &v) {

  }
  // set sentinel val
  void set() {

  }
  // debug
  friend ostream &operator<<(ostream &cout, Info x) {
      return cout;
  };
};

using Tree = linkCutTree<Info>;