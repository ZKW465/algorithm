template<int N>
class tree {
public:
  int n, K;
  vector<vector<int>> adj;
  vector<array<int, __lg(N) + 1>> p;
  vector<int> dep;
  tree() {};
  tree(int n_) : n(n_), adj(n_), p(n_), dep(n_), K(__lg(n_) + 1) {}

  void add(int u, int v) {
    adj[u].emplace_back(v);
    adj[v].emplace_back(u);
  }

  void work(int root = 0) {
    dfs(root, root);
  }

  void dfs(int u, int f) {
    p[u][0] = f;
    for (int i = 1; i < K; i += 1) {
      p[u][i] = p[p[u][i - 1]][i - 1];
    }
    for (int v : adj[u]) {
      if (v == f) {
        continue;
      }
      dep[v] = dep[u] + 1;
      dfs(v, u);
    }
  }

  int jump_to(int u, int d) {
    for (int i = dep[u] - d; i > 0; i -= 1 << __lg(i)) {
      u = p[u][__lg(i)];
    }
    return u;
  }

  int lca(int u, int v) {
    if (dep[u] < dep[v]) {
      swap(u, v);
    }
    u = jump_to(u, dep[v]);
    if (u == v) {
      return u;
    }
    for (int i = __lg(dep[u]); i >= 0; i -= 1) {
      if (p[u][i] != p[v][i]) {
        u = p[u][i], v = p[v][i];
      }
    }
    return p[u][0];
  }

  int dist(int u, int v) {
    int m = lca(u, v);
    return dep[u] + dep[v] - 2 * dep[m];
  }
};