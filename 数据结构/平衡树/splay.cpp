struct node;
using Tp = safe_ptr<node>;
struct node {
  Tp l, r, p;
  int siz;
  i64 val;
  i64 sum;
  i64 tag;
  node(i64 val_) {
    siz = 1;
    val = val_;
    sum = val;
    tag = 0;
  }
  void push() {
    if (tag) {
      l->apply(tag);
      r->apply(tag);
      tag = 0;
    }
  }
  void pull() {
    siz = l->siz + 1 + r->siz;
    sum = l->sum + val + r->sum;
  }
  void apply(auto c) {
    if (siz) {
      val += c;
      sum += 1ll * siz * c;
      tag += c;
    }
  };
  void pushall() {
    if (p)
      p->pushall();
    push();
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
  t->pushall();
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
    i->push();
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
    t->push();
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
  i->push();
  while (i->r) {
    i = i->r, i->push();
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
  t->push();
  dfs(t->l, dep + 1);
  for (int i = 0; i < dep; i += 1)
    cerr << '\t';
  cerr << t->val << " " << t->sum << "\n";
  dfs(t->r, dep + 1);
}
