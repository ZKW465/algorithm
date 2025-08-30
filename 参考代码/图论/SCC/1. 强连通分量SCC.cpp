struct SCC {
  int n;
  vector<int> h, t, to;
  vector<int> stk;
  vector<int> dfn, low, bel;
  int cur, cnt;

  SCC(int n) {
    init(n);
  }

  void init(int n) {
    this->n = n;
    h.assign(n, -1);
    dfn.assign(n, -1);
    low.resize(n);
    bel.assign(n, -1);
    stk.clear();
    cur = cnt = 0;
  }

  void addEdge(int u, int v) {
    t.push_back(h[u]), h[u] = to.size(), to.push_back(v);
  }

  void tarjan(int u) {
    dfn[u] = low[u] = cur++;
    stk.push_back(u);

    for (int i = h[u]; i != -1; i = t[i]) {
      int v = to[i];
      if (dfn[v] == -1) {
        tarjan(v);
        low[u] = min(low[u], low[v]);
      } else if (bel[v] == -1) {
        low[u] = min(low[u], dfn[v]);
      }
    }

    if (dfn[u] == low[u]) {
      int v = -1;
      do {
        v = stk.back();
        bel[v] = cnt;
        stk.pop_back();
      } while (v != u);
      cnt++;
    }
  }

  vector<int> work() {
    for (int i = 0; i < n; i++) {
      if (dfn[i] == -1) {
        tarjan(i);
      }
    }
    return bel;
  }

  vector<vector<int>> Graph() {
    vector<vector<int>> g(cnt);
    for (int u = 0; u < n; u += 1) {
      for (int i = h[u]; i != -1; i = t[i]) {
        int v = to[i];
        if (bel[u] != bel[v]) {
          g[bel[u]].push_back(bel[v]);
        }
      }
    }
    return g;
  }

  vector<array<int, 2>> Edges() {
    vector<array<int, 2>> e;
    for (int u = 0; u < n; u += 1) {
      for (int i = h[u]; i != -1; i = t[i]) {
        int v = to[i];
        if (bel[u] != bel[v]) {
          e.push_back({bel[u], bel[v]});
        }
      }
    }
    sort(e.begin(), e.end());
    e.erase(unique(e.begin(), e.end()), e.end());
    return e;
  }
};