#pragma once

#include "zedui/events/event_processor.h"

namespace zedui {
class EventTarget;
class EventTargeter;
class WindowTreeHost;
class Window;
class WindowEventDispatcher : public EventProcessor {
 public:
 public:
  explicit WindowEventDispatcher(WindowTreeHost* host);
  ~WindowEventDispatcher() override = default;

  WindowTreeHost* host() { return host_; }

  // EventSink overrides
  EventTarget* GetRootForEvent(Event* event) override;
  virtual EventTargeter* GetDefaultEventTargeter() override;

 private:
  Window* window();
  const Window* window() const;

  WindowTreeHost* host_;
};
}  // namespace zedui