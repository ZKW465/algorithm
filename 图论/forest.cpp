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
  vector<vector<int>> ids;
  forest(int n_) : n(n_), ids(n_) {}
  void add(int from, int to, T cost = 1) {
    int id = edges.size();
    ids[from].emplace_back(id);
    ids[to].emplace_back(id);
    edges.emplace_back(from, to, cost);
  }
};