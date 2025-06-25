#include <ext/random>
__gnu_cxx::sfmt19937
    rng(std::chrono::steady_clock::now().time_since_epoch().count());

struct node;
using Tp = safe_ptr<node>;

struct node {
  bool rev;
  Tp l, r;
  int siz, k;
  i64 val;
  i64 tag;
  node(i64 val_) {
    siz = 1;
    k = rng();
    val = val_;
    rev = 0;
    tag = 0;
  }
  void apply(auto c) {
    if (siz == 0) {
      return;
    }
    val += c;
    tag += c;
  }
  void push_stuff() {
    if (tag) {
      l->apply(tag);
      r->apply(tag);
      tag = 0;
    }
  }
  void reverse() {
    rev ^= 1;
  }
  void pull() {
    siz = l->siz + 1 + r->siz;
  }
  void push() {
    if (rev) {
      std::swap(l, r);
      l->reverse();
      r->reverse();
      rev = 0;
    }
    push_stuff();
  }
};

// must run once
void make_sentinnel() {
  Tp t = make_safe<node>(0);
  t->siz = 0;
}

// to [-inf, val) and [val, inf]
pair<Tp, Tp> split1(Tp t, auto val) {
  if (!t) {
    return {t, t};
  }
  t->push();
  Tp u;
  if (t->val < val) {
    tie(t->r, u) = split1(t->r, val);
    t->pull();
    return {t, u};
  } else {
    tie(u, t->l) = split1(t->l, val);
    t->pull();
    return {u, t};
  }
}

// to [1, k) and [k, n]
pair<Tp, Tp> split2(Tp t, int k) {
  if (!t) {
    return {t, t};
  }
  t->push();
  Tp u;
  if (k <= t->l->siz) {
    tie(u, t->l) = split2(t->l, k);
    t->pull();
    return {u, t};
  } else if (k > t->l->siz + 1) {
    tie(t->r, u) = split2(t->r, k - 1 - t->l->siz);
    t->pull();
    return {t, u};
  } else {
    u = t->l;
    t->l = 0;
    t->pull();
    return {u, t};
  }
}

Tp merge(Tp u, Tp v) {
  if (!u || !v)
    return u | v;
  if (u->k < v->k) {
    u->push();
    u->r = merge(u->r, v);
    u->pull();
    return u;
  } else {
    v->push();
    v->l = merge(u, v->l);
    v->pull();
    return v;
  }
}

void dfs(Tp t, int dep = 0) {
  if (!t) {
    return;
  }
  dfs(t->l, dep + 1);
  for (int i = 0; i < dep; i += 1)
    cerr << '\t';
  cerr << t->val << " " << t->tag << " " << t->siz << '\n';
  dfs(t->r, dep + 1);
}

// count less siz
int count_less(Tp t, auto val) {
  int less_siz = 0;
  while (t) {
    t->push();
    if (t->val >= val) {
      t = t->l;
    } else {
      less_siz += t->l->siz + 1;
      t = t->r;
    }
  }
  return less_siz;
}

// from one
Tp kth_element(Tp t, int k) {
  while (true) {
    t->push();
    if (t->l->siz >= k) {
      t = t->l;
    } else if (t->l->siz + 1 < k) {
      k -= t->l->siz + 1;
      t = t->r;
    } else
      break;
  }
  return t;
}

// the first element before val
Tp prev(Tp t, auto val) {
  Tp p;
  while (t) {
    t->push();
    if (t->val < val) {
      p = t;
      t = t->r;
    } else {
      t = t->l;
    }
  }
  return p;
}

// the first element next to val
Tp next(Tp t, auto val) {
  Tp p;
  while (t) {
    t->push();
    if (t->val <= val) {
      t = t->r;
    } else {
      p = t;
      t = t->l;
    }
  }
  return p;
}