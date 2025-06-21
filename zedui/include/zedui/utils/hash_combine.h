#ifndef ZEDUI_UTILS_HASH_COMBNINE_H_
#define ZEDUI_UTILS_HASH_COMBNINE_H_

#include <functional>
#include <type_traits>

namespace zedui {
template <typename T>
concept Hashable = !std::is_same_v<T, const char*> && (requires(T a) {
  { std::hash<T>{}(a) } -> std::convertible_to<std::size_t>;
});

template <Hashable T, Hashable... Rest>
void HashCombine(std::size_t& seed, const T& v, const Rest&... rest) {
  seed ^= std::hash<T>{}(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
  (HashCombine(seed, rest), ...);
}

template <Hashable T, Hashable... Args>
std::size_t HashCombine(const T& v, const Args&... args) {
  std::size_t seed = 0;
  HashCombine<T, Args...>(seed, v, args...);
  return seed;
}
}  // namespace zedui

#endif  // ZEDUI_UTILS_HASH_COMBNINE_H_