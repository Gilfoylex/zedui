#pragma once
#include <memory>
#include "zedui/events/event_targeter.h"

namespace zedui {
class Rect;
class View;
class ViewTargeterDelegate;
class ViewTargeter : public EventTargeter {
    public:
  explicit ViewTargeter(ViewTargeterDelegate* delegate);
  explicit ViewTargeter(std::unique_ptr<ViewTargeterDelegate> delegate);

  ViewTargeter(const ViewTargeter&) = delete;
  ViewTargeter& operator=(const ViewTargeter&) = delete;

  ~ViewTargeter() override = default;

  // A call-through to DoesIntersectRect() on `delegate_`.
  bool DoesIntersectRect(const View* target, const Rect& rect) const;
  // A call-through to TargetForRect() on `delegate_`.
  View* TargetForRect(View* root, const Rect& rect) const;

  // EventTargeter overrides:
  EventTarget* FindTargetForEvent(EventTarget* root, Event* event) override;

  private:
   std::unique_ptr<ViewTargeterDelegate> owned_delegate_;
   ViewTargeterDelegate* delegate_;
};

}  // namespace zedui