template<typename T>
vector<T> pool;

template<typename T>
class safe_ptr {
  int off;
public:
  safe_ptr(int off_ = 0) : off(off_) {}

  T* operator->() {
    return pool<T>.data() + off;
  }
  T& operator*() {
    return pool<T>[off];
  }
  operator int() const { return off; }
  bool operator==(safe_ptr v) { return off == v.off; }
};

template<typename T, typename... Args>
safe_ptr<T> make_safe(Args&&... args) {
  pool<T>.emplace_back(forward<Args>(args)...);
  return safe_ptr<T>(pool<T>.size() - 1);
}