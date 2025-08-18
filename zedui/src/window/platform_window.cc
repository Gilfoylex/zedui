#include "zedui/window/platform_window.h"
#include "zedui/window/window_event_dispatcher.h"

namespace zedui {

EventSink* PlatformWindow::GetEventSink() {
  return dispatcher_.get();
}

} // namespace zedui