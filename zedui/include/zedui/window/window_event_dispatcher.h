#pragma once

#include "zedui/events/event_processor.h"

namespace zedui {
class EventTarget;
class EventTargeter;
class PlatformWindow;
class WindowEventDispatcher : public EventProcessor {
 public:
 public:
  explicit WindowEventDispatcher();
  ~WindowEventDispatcher() override = default;

  // EventSink overrides
  EventTarget* GetRootForEvent(Event* event) override;
  virtual EventTargeter* GetDefaultEventTargeter() override;

 private:
  PlatformWindow* window();
  const PlatformWindow* window() const;
};
}  // namespace zedui