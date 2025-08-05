template<typename T, 
    typename KeyTypeComparator = less<T>>
class SparseTable {
 public:
  SparseTable() = default;
  SparseTable(const vector<T>& array) {
    init(array);
  }
  void init(const vector<T>& array) {
    n_ = array.size();
    int k = __lg(n_) + 1;
    array_.assign(k, {});
    array_[0] = array;
    for (int i = 1, siz = 2; i < k; i += 1, siz *= 2) {
      array_[i].assign(n_, 0);
      for (int j = 0; j + siz - 1 < n_; j ++) {
        array_[i][j] = std::max(array_[i - 1][j], 
            array_[i - 1][j + (siz >> 1)], comp_);
      }
    }
  }
  // [l, r]
  T operator()(int l, int r) {
    int k = __lg(r - l + 1);
    return std::max(array_[k][l], 
        array_[k][r - (1 << k) + 1], comp_);
  }
 private:
  int n_;
  vector<vector<T>> array_;
  static constexpr KeyTypeComparator comp_;
};