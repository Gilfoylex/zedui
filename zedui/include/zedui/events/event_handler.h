#pragma once
#include "zedbase/macros.h"

namespace zedui {
class CancelModeEvent;
class Event;
class MouseEvent;
class EventHandler {
 public:
  virtual ~EventHandler() = default;
  virtual void OnEvent(Event* event);
  virtual void OnCancelMode(CancelModeEvent* event);
  virtual void OnMouseEvent(MouseEvent* event);
};
}  // namespace zedui