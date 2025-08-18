#include "zedui/views/view.h"
#include "zedui/views/view_targeter_delegate.h"

namespace zedui {
bool ViewTargeterDelegate::DoesIntersectRect(const View* target,
                                             const Rect& rect) const {}

View* ViewTargeterDelegate::TargetForRect(View* root,
                                          const Rect& rect) {
  return nullptr;
}

}  // namespace zedui