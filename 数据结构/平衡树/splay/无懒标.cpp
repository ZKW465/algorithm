struct node;
using Tp = safe_ptr<node>;
struct node {
  Tp l, r, p;
  int siz;
  i64 val;
  i64 sum;
  node(i64 val_) {
    siz = 1;
    val = val_;
    sum = val;
  }
  void pull() {
    siz = l->siz + 1 + r->siz;
    sum = l->sum + val + r->sum;
  }
};

// must run once
void make_sentinnel() {
  Tp t = make_safe<node>(0);
  t->siz = 0;
}

bool pos(Tp t) { return t->p->r == t; }

void rotate(Tp t) {
  Tp q = t->p;
  if (!pos(t)) {
    q->l = t->r;
    if (t->r) 
      t->r->p = q;
    t->r = q;
  } else {
    q->r = t->l;
    if (t->l) 
      t->l->p = q;
    t->l = q;
  }
  t->p = q->p;
  if (q->p) 
    (pos(q) ? q->p->r : q->p->l) = t;
  q->p = t;
  q->pull();
}

void splay(Tp t, Tp top = 0) {
  while (t->p != top) {
    if (t->p->p != top)
      rotate(pos(t) ^ pos(t->p) ? t : t->p);
    rotate(t);
  }
  t->pull();
}

// to [-inf, val) and [val, inf]
pair<Tp, Tp> split1(Tp t, auto x) {
  if (!t) {
    return {t, t};
  }
  Tp v = 0;
  Tp j = t;
  for (Tp i = t; i;) {
    j = i;
    if (i->val >= x) {
      v = i;
      i = i->l;
    } else {
      i = i->r;
    }
  }

  splay(j);
  if (!v) {
    return {j, 0};
  }

  splay(v);

  Tp u = v->l;
  if (u) {
    v->l = u->p = 0;
    v->pull();
  }
  return {u, v};
}

// 从 1 开始
void splay_kth(Tp &t, int k) {
  while (true) {
    if (k > t->l->siz + 1) {
      k -= t->l->siz + 1;
      t = t->r;
    } else if (k <= t->l->siz) {
      t = t->l;
    } else {
      break;
    }
  }
  splay(t);
}

// to [1, x) and [x, n]
pair<Tp, Tp> split2(Tp t, int x) {
  if (t->siz < x) {
    return {t, 0};
  }

  splay_kth(t, x);

  Tp u = t->l;
  if (u) {
    t->l = u->p = 0;
    t->pull();
  }
  return {u, t};
}

Tp merge(Tp l, Tp r) {
  if (!l || !r) {
    return l | r;
  }
  Tp i = l;
  while (i->r) {
    i = i->r;
  }
  splay(i);
  i->r = r;
  r->p = i;
  i->pull();
  return i;
}

void dfs(Tp t, int dep = 0) {
  if (!t) {
    return;
  }
  dfs(t->l, dep + 1);
  for (int i = 0; i < dep; i += 1)
    cerr << '\t';
  cerr << t->val << " " << t->sum << "\n";
  dfs(t->r, dep + 1);
}

// count less siz
int count_less(Tp& t, auto val) {
  int less_siz = 0;
  Tp p;
  while (t) {
    p = t;
    if (t->val >= val) {
      t = t->l;
    } else {
      less_siz += t->l->siz + 1;
      t = t->r;
    }
  }
  splay(p);
  t = p;
  return less_siz;
}

// from one 
Tp kth_element(Tp& t, int k) {
  splay_kth(t, k);
  return t;
}

// the first element before val
Tp prev(Tp& t, auto val) {
  Tp p;
  while (t) {
    if (t->val < val) {
      p = t;
      t = t->r;
    } else {
      t = t->l;
    }
  }
  splay(p);
  t = p;
  return p;
}

// the first element next to val
Tp next(Tp& t, auto val) {
  Tp p;
  while (t) {
    if (t->val <= val) {
      t = t->r;
    } else {
      p = t;
      t = t->l;
    }
  }
  splay(p);
  t = p;
  return p;
}