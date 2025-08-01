#pragma once
#include <stack>

#include "zedbase/macros.h"

namespace zedui {
class EventDispatcher;
class EventTarget;
class CancelModeEvent;
class Event;
class MouseEvent;
class EventHandler {
 public:
  virtual ~EventHandler() = default;
  virtual void OnEvent(Event* event);
  virtual void OnCancelMode(CancelModeEvent* event);
  virtual void OnMouseEvent(MouseEvent* event);

 private:
  friend class EventDispatcher;
  friend class EventTarget;

  std::stack<EventDispatcher*> dispatchers_;
};
using EventHandlerList = std::vector<EventHandler*>;
}  // namespace zedui