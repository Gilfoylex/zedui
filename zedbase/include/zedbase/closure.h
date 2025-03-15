#ifndef ZEDBASE_CLOSURE_H_
#define ZEDBASE_CLOSURE_H_

#include <functional>
#include "zedbase/macros.h"

namespace zedbase {
using closure = std::function<void()>;

//------------------------------------------------------------------------------
/// @brief      Wraps a closure that is invoked in the destructor unless
///             released by the caller.
///
///             This is especially useful in dealing with APIs that return a
///             resource by accepting ownership of a sub-resource and a closure
///             that releases that resource. When such APIs are chained, each
///             link in the chain must check that the next member in the chain
///             has accepted the resource. If not, it must invoke the closure
///             eagerly. Not doing this results in a resource leak in the
///             erroneous case. Using this wrapper, the closure can be released
///             once the next call in the chain has successfully accepted
///             ownership of the resource. If not, the closure gets invoked
///             automatically at the end of the scope. This covers the cases
///             where there are early returns as well.
///
class ScopedCleanupClosure final {
 public:
  ScopedCleanupClosure() = default;

  ScopedCleanupClosure(ScopedCleanupClosure&& other) {
    closure_ = other.Release();
  }

  ScopedCleanupClosure& operator=(ScopedCleanupClosure&& other) {
    closure_ = other.Release();
    return *this;
  }

  explicit ScopedCleanupClosure(const zedbase::closure& closure)
      : closure_(closure) {}

  ~ScopedCleanupClosure() { Reset(); }

  zedbase::closure SetClosure(const zedbase::closure& closure) {
    auto old_closure = closure_;
    closure_ = closure;
    return old_closure;
  }

  zedbase::closure Release() {
    zedbase::closure closure = closure_;
    closure_ = nullptr;
    return closure;
  }

  void Reset() {
    if (closure_) {
      closure_();
      closure_ = nullptr;
    }
  }

 private:
  zedbase::closure closure_;

  ZED_DISALLOW_COPY_AND_ASSIGN(ScopedCleanupClosure);
};

}  // namespace zedbase

#endif  // ZEDBASE_CLOSURE_H_