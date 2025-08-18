#include "zedui/window/window_event_dispatcher.h"
#include "zedui/window/platform_window.h"

namespace zedui {

WindowEventDispatcher::WindowEventDispatcher()
     {}

EventTarget* WindowEventDispatcher::GetRootForEvent(Event* event) {

}

Window* WindowEventDispatcher::window() {
  return nullptr;
}

const Window* WindowEventDispatcher::window() const {
  return nullptr;
}

} // namespace zedui