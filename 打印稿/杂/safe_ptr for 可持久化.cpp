/**
 * 1 MB = 1024 KB
 * 1 KB = 1024 B
 * 134'210'000    128
 * 262'144'000    256
 * 520'000'000    524
 * 1'030'000'000  1024
 * 注意事项：记得内存别开小了或者别爆了
 */

constexpr int max_size = 262'144'000;
uint8_t buf[max_size];
uint8_t* head = buf;

template<typename T>
class safe_ptr {
  int off;
public:
  safe_ptr(int off_ = 0) : off(off_) {}

  T* operator->() {
    return reinterpret_cast<T*>(buf + off);
  }
  T& operator*() {
    return *reinterpret_cast<T*>(buf + off);
  }
  operator int() const { return off; }
  bool operator==(safe_ptr v) { return off == v.off; }
};

template<typename T, typename... Args>
safe_ptr<T> make_safe(Args&&... args) {
  head += sizeof(T);

  assert(head + sizeof(T) <= buf + max_size);
  int off = static_cast<int>(head - buf);

  T* obj = new (head) T(std::forward<Args>(args)...);
  return safe_ptr<T>(off);
}