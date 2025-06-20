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
