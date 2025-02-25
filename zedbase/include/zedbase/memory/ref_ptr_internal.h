#ifndef REF_PTR_INTERNAL_H_
#define REF_PTR_INTERNAL_H_

namespace zedbase {
    

template <typename T>
class RefPtr;

template <typename T>
RefPtr<T> AdoptRef(T* ptr);

namespace internal {

// This is a wrapper class that can be friended for a particular |T|, if you
// want to make |T|'s constructor private, but still use |MakeRefCounted()|
// (below). (You can't friend partial specializations.) See |MakeRefCounted()|
// and |FML_FRIEND_MAKE_REF_COUNTED()|.
template <typename T>
class MakeRefCountedHelper final {
 public:
  template <typename... Args>
  static RefPtr<T> MakeRefCounted(Args&&... args) {
    return AdoptRef<T>(new T(std::forward<Args>(args)...));
  }
};

}  // namespace internal
}  // namespace zedbase

#endif // REF_PTR_INTERNAL_H_