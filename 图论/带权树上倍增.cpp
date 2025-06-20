template <typename T> 
class forest {
public:
  struct edge {
    int from;
    int to;
    T cost;
  };
  int n;
  vector<edge> edges;
  vector<int> ids;
  forest(int n_) : n(n_), ids(n_ + 1) {}
  void add(int from, int to, T cost = 1) {
    ids[from + 1]++;
    ids[to + 1]++;
    edges.emplace_back(from, to, cost);
  }
  void init() { 
    for (int i = 1; i <= n; i++) {
      ids[i] += ids[i - 1];
    }
    auto cnt = ids;
    auto last = edges;
    for (auto& edge : last) {
      edges[cnt[edge.first]++] = edge;
    }
  }
};

template<typename T, int N>
class multiTree : public forest<T> {
public:
  using forest<T>::n;
  using forest<T>::edges;
  using forest<T>::ids;
  int K;
  vector<array<int, __lg(N) + 1>> p;
  vector<int> dep;
  vector<T> dep2;
  multiTree();
  multiTree(int n_) : forest<T>(n_), p(n_), dep(n), dep2(n), K(__lg(n) + 1) {}

  void work(int root = 0) {
    forest<T>::init();
    dfs(root, root);
  }

  void dfs(int u, int f) {
    p[u][0] = f;
    for (int i = 1; i < K; i += 1) {
      p[u][i] = p[p[u][i - 1]][i - 1];
    }
    for (int i = ids[u]; i < ids[u + 1]; i += 1) {
      auto [from, to, cost] = edges[i];
      int v = u ^ from ^ to;
      if (v == f) {
        continue;
      }
      dep[v] = dep[u] + 1;
      dep2[v] = dep2[u] + cost;
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

  T dis2(int u, int v) {
    int m = lca(u, v);
    return dep2[u] + dep2[v] - 2 * dep[m];
  }
};
