#pragma once

#include <memory>
#include <type_traits>

namespace zedbase {
// Helper to transfer ownership of a raw pointer to a std::unique_ptr<T>.
// Note that std::unique_ptr<T> has very different semantics from
// std::unique_ptr<T[]>: do not use this helper for array allocations.
template <typename T>
  requires(std::is_object_v<T> && !std::is_array_v<T>)
std::unique_ptr<T> WrapUnique(T* ptr) {
  return std::unique_ptr<T>(ptr);
}
}  // namespace zedbase