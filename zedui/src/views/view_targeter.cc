#include "zedbase/logging.h"
#include "zedui/views/view_targeter.h"
#include "zedui/views/view_targeter_delegate.h"

namespace zedui {

ViewTargeter::ViewTargeter(ViewTargeterDelegate* delegate)
    : delegate_(delegate) {
  ZED_DCHECK(delegate_);
}

ViewTargeter::ViewTargeter(std::unique_ptr<ViewTargeterDelegate> delegate)
    : owned_delegate_(std::move(delegate)), delegate_(owned_delegate_.get()) {
  ZED_DCHECK(delegate_);
}

bool ViewTargeter::DoesIntersectRect(const View* target,
                                     const Rect& rect) const {
  return delegate_->DoesIntersectRect(target, rect);
}

View* ViewTargeter::TargetForRect(View* root, const Rect& rect) const {
  return delegate_->TargetForRect(root, rect);
}

}  // namespace zedui