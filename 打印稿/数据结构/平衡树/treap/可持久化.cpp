#include <ext/random>
__gnu_cxx::sfmt19937
    rng(std::chrono::steady_clock::now().time_since_epoch().count());

struct node;
using Tp = safe_ptr<node>;

Tp clone(Tp u);

struct node {
  Tp l, r;
  int siz, k;
  i64 val;
  node(i64 val_ = 0) {
    siz = 1;
    k = rng();
    val = val_;
    l = r = 0;
  }
  void pull() { siz = l->siz + 1 + r->siz; }
};

Tp clone(Tp u) {
  if (!u) {
    return u;
  }
  Tp p = make_safe<node>();
  *p = *u;
  return p;
}

// must run once
void make_sentinnel() {
  Tp t = make_safe<node>(0);
  t->siz = 0;
}

// to [1, val) and [val, n]
pair<Tp, Tp> split1(Tp t, auto val) {
  if (!t) {
    return {0, 0};
  }
  t = clone(t);
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
  t = clone(t);
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
    u = clone(u);
    u->r = merge(u->r, v);
    u->pull();
    return u;
  } else {
    v = clone(v);
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
  cerr << t->siz << ' ' << t->val << ' ' << '\n';
  dfs(t->r, dep + 1);
}

// count less siz
int count_less(Tp t, auto val) {
  int less_siz = 0;
  while (t) {
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
    if (t->val <= val) {
      t = t->r;
    } else {
      p = t;
      t = t->l;
    }
  }
  return p;
}

Tp insert(Tp t, Tp v) {
  if (!t) {
    return v;
  }
  t = clone(t);
  if (t->k < v->k) {
    tie(v->l, v->r) = split1(t, v->val);
    v->pull();
    return v;
  }
  t->siz += 1;
  if (v->val > t->val || (t->val == v->val && int(rng()) >= 0)) {
    t->r = insert(t->r, v);
  } else {
    t->l = insert(t->l, v);
  }
  t->pull();
  return t;  
}

Tp erase(Tp t, auto v) {
  if (!t) {
    return t;
  }
  t = clone(t);
  if (t->val == v) {
    t = merge(t->l, t->r);
    return t;
  } else {
    if (v > t->val) {
      t->r = erase(t->r, v);
    } else {
      t->l = erase(t->l, v);
    }
    t->pull();
    return t;
  }
}