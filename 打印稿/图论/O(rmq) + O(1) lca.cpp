template<typename T, 
    typename Cmp = less<T>>
struct SparseTable {
  int n;
  vector<vector<T>> pre;
  Cmp cmp;
  SparseTable() = default;
  SparseTable(vector<T>& c) {
    init(c);
  }
  void init(vector<T>& c) {
    n = c.size();
    int k = __lg(n) + 1;
    pre.assign(k, {});
    pre[0] = c;
    for (int i = 1, sz = 2; i < k; i += 1, sz *= 2) {
      pre[i].assign(n, 0);
      for (int j = 0; j + sz - 1 < n; j ++) {
        pre[i][j] = std::max(pre[i - 1][j], pre[i - 1][j + (sz >> 1)], cmp);
      }
    }
  }
  T operator()(int l, int r) {
    T k = __lg(r - l + 1);
    return std::max(pre[k][l], pre[k][r - (1 << k) + 1], cmp);
  }
};

struct Tree {
  int n, cur;
  vector<vector<int>> adj;
  vector<int> in, out, dep, siz, fa, seq, init_;
  SparseTable<int, std::greater<>> rmq;
  Tree() = default;
  Tree(int n) {
    init(n);
  }
  void init(int n) {
    this->n = n;
    adj.assign(n, {});
  }
  void addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  void work(int root = 0) {
    in.assign(n, 0);
    out.assign(n, 0);
    dep.assign(n, 0);
    siz.assign(n, 1);
    fa.assign(n, 0);
    seq.assign(n, 0);
    init_.assign(n, 0);
    cur = 0;
    dfs(root, root);
    rmq.init(init_);
  }
  void dfs(int u, int p) {
    init_[cur] = in[p];
    seq[in[u] = cur++] = u;
    dep[u] = dep[p] + 1;
    fa[u] = p;
    for (auto v : adj[u]) {
      if (v == p) continue;
      dfs(v, u);
      siz[u] += siz[v];
    }
    out[u] = cur;
  }
  int lca(int u, int v) {
    if (u == v) return u;
    if ((u = in[u]) > (v = in[v])) swap(u, v); 
    return seq[rmq(u + 1, v)];
  }
};