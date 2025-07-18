#pragma once

namespace zedui {
class View;
class ContainerView;
class Rect;

class ViewTargeterDelegate {
 public:
  ViewTargeterDelegate() = default;
  ViewTargeterDelegate(const ViewTargeterDelegate&) = delete;
  ViewTargeterDelegate& operator=(const ViewTargeterDelegate&) = delete;
  virtual ~ViewTargeterDelegate() = default;

  virtual bool DoesIntersectRect(const View* target, const Rect& rect) const;

  // Returns true if the event should be handled by the target view.
  virtual View* TargetForRect(ContainerView* root, const Rect& rect);
};

}  // namespace zedui