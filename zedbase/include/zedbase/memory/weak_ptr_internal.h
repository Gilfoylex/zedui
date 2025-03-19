#ifndef ZEDBASE_MEMORY_WEAK_PTR_INTERNAL_H_
#define ZEDBASE_MEMORY_WEAK_PTR_INTERNAL_H_

#include "zedbase/macros.h"
#include "zedbase/memory/ref_counted.h"

namespace zedbase {
namespace internal {

// |WeakPtr<T>|s have a reference to a |WeakPtrFlag| to determine whether they
// are valid (non-null) or not. We do not store a |T*| in this object since
// there may also be |WeakPtr<U>|s to the same object, where |U| is a superclass
// of |T|.
//
// This class in not thread-safe, though references may be released on any
// thread (allowing weak pointers to be destroyed/reset/reassigned on any
// thread).
class WeakPtrFlag : public zedbase::RefCountedThreadSafe<WeakPtrFlag> {
 public:
  WeakPtrFlag();

  ~WeakPtrFlag();

  bool is_valid() const { return is_valid_; }

  void Invalidate();

 private:
  bool is_valid_ = false;

  ZED_DISALLOW_COPY_AND_ASSIGN(WeakPtrFlag);
};

}  // namespace internal
}  // namespace zedbase

#endif  // ZEDBASE_MEMORY_WEAK_PTR_INTERNAL_H_