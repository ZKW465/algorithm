vector<int> centroid(const vector<vector<int>>& adj) {
    int n = adj.size();
    vector<bool> used(n);
    vector<int> siz(n);
    vector<int> res;
    res.reserve(n);
    auto dfs = [&](auto &&dfs, int u, int p) -> void {
      siz[u] = 1;
      for (auto v : adj[u]) {
        if (v == p || used[v]) {
          continue;
        }
        dfs(dfs, v, u);
        siz[u] += siz[v];
      }
    };
    auto find = [&](int x) {
      dfs(dfs, x, x);
      int p = -1;
      int u = x;
      int n = siz[x];
      while (true) {
        int y = -1;
        for (auto v : adj[u]) {
          if (v == p || used[v]) {
            continue;
          }
          if (siz[v] * 2 > n) {
            y = v;
            break;
          }
        }
        if (y == -1) {
          break;
        }
        p = u;
        u = y;
      }
      used[u] = true;
      return u;
    };
    for (int i = 0; i < n; i++) {
      while (!used[i]) {
        res.push_back(find(i));
      }
    }
    return res;
}
