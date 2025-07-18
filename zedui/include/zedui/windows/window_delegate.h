#pragma once
#include "zedui/events/event_handler.h"

namespace zedui {
class WindowDelegate : public EventHandler {
 public:
  virtual void OnCreated() = 0;
  virtual void OnDestroyed() = 0;
  virtual void OnSizeChanged(int width, int height) = 0;

 protected:
  ~WindowDelegate() override {}
};
}  // namespace zedui