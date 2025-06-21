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
  vector<int> dfn, dep, siz, fa, seq, dnp;
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
    dfn.assign(n, 0);
    dep.assign(n, 0);
    siz.assign(n, 1);
    fa.assign(n, 0);
    seq.assign(n, 0);
    dnp.assign(n, 0);
    cur = 0;
    dfs(root, root);
    rmq.init(dnp);
  }
  void dfs(int u, int p) {
    dnp[cur] = dfn[p];
    seq[dfn[u] = cur++] = u;
    dep[u] = dep[p] + 1;
    fa[u] = p;
    for (auto v : adj[u]) {
      if (v == p) continue;
      dfs(v, u);
      siz[u] += siz[v];
    }
  }
  int lca(int u, int v) {
    if (u == v) return u;
    if ((u = dfn[u]) > (v = dfn[v])) swap(u, v); 
    return seq[rmq(u + 1, v + 1)];
  }
};

class VirtualTree : public Tree {
public:
  VirtualTree(int n) : Tree(n), vTree(n), stk(n) {};

  vector<vector<int>>& build(vector<int> &key) {
    sort(key.begin(), key.end(), 
        [&] (int x, int y) {return dfn[x] < dfn[y];});
    int cur = 0;
    vTree[0].clear();
    for (int i = key[0] == 0; i < key.size(); i += 1) {
      int Lca = lca(key[i], stk[cur]);
      if (Lca != stk[cur]) {
        while(dfn[Lca] < dfn[stk[cur - 1]]) {
          vTree[stk[cur - 1]].push_back(stk[cur--]);
        }
        if (Lca != stk[cur - 1]) {
          vTree[Lca].clear();
          vTree[Lca].push_back(stk[cur]); stk[cur] = Lca;
        } else {
          vTree[Lca].push_back(stk[cur--]);
        }
      }
      vTree[key[i]].clear();
      stk[++cur] = key[i];
    }
    for (int i = 0; i < cur; i += 1) {
      vTree[stk[i]].push_back(stk[i + 1]);
    }
    return vTree;
  }
private:
  vector<int> stk;
  vector<vector<int>> vTree;
};
