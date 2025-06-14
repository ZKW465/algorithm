#include <ext/random>
__gnu_cxx::sfmt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

struct node;
using Tp = Base<node>;

struct node {
    Tp ch[2];
    int siz, k;
    i64 val;
    i64 tag;
};

Tp alloc() {
    Tp t = Tp::alloc();
    t->k = rng();
    return t;
}

Tp alloc(Tp u) {
    if (!u) {
        return u;
    }
    Tp p = Tp::alloc();
    *p = *u;
    return p;
}

void app(Tp t, auto tag) {
    if (!t) {
        return;
    }
    t->val += tag;
    t->tag += tag;
}

void push(Tp t) {
    if (t->tag) {
        t->ch[0] = alloc(t->ch[0]);
        t->ch[1] = alloc(t->ch[1]);
        app(t->ch[0], t->tag);
        app(t->ch[1], t->tag);
        t->tag = decltype(t->tag)();
    }
}

void pull(Tp t) {
    t->siz = t->ch[0]->siz + 1 + t->ch[1]->siz;
}


pair<Tp, Tp> split1(Tp &t, auto val) {
    if (!t) {
        return {0, 0};
    }
    t = alloc(t);
    push(t);
    Tp u;
    if (t->val < val) {
        tie(t->ch[1], u) = split1(t->ch[1], val);
        pull(t);
        return {t, u};
    } else {
        tie(u, t->ch[0]) = split1(t->ch[0], val);
        pull(t);
        return {u, t};
    }
}

pair<Tp, Tp> split2(Tp t, int rk) {
    if (!t) {
        return {t, t};
    }
    push(t);
    t = alloc(t);
    Tp u;
    if (rk <= t->ch[0]->siz) {
        tie(u, t->ch[0]) = split2(t->ch[0], rk);
        pull(t);
        return {u, t};
    } else {
        tie(t->ch[1], u) = split2(t->ch[1], rk - 1 - t->ch[0]->siz);
        pull(t);
        return {t, u};
    }
}

template<bool isNew = false>
Tp merge(Tp u, Tp v) {
    if (!u | !v) return u.x | v.x;
    if (u->key < v->key) {
        push(u);
        if (isNew) {
            u = alloc(u);
        }
        u->ch[1] = merge<isNew>(u->ch[1], v);
        pull(u);
        return u;
    } else {
        push(v);
        if (isNew) {
            v = alloc(v);
        }
        v->ch[0] = merge<isNew>(u, v->ch[0]);
        pull(v);
        return v;
    }
}