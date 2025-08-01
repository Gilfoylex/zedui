#pragma once

#include "zedui/events/event_source.h"
#include "zedui/window/platform_window.h"

#include "zedbase/memory/weak_ptr.h"

namespace zedui {
class WindowTreeHost : public EventSource {
 public:
  ~WindowTreeHost() override;
  PlatformWindow* GetWindow() { return window_; }
  const PlatformWindow* GetWindow() const { return window_; }

  zedbase::WeakPtr<WindowTreeHost> GetWeakPtr();

  // EventSource overrides
  EventSink* GetEventSink() override;

protected:
  PlatformWindow* window_;
  float device_scale_factor_ = 1.0f;
  zedbase::WeakPtrFactory<WindowTreeHost> weak_ptr_factory_{this};
};
}  // namespace zedui