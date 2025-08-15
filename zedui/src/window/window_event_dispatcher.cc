#include "zedui/window/window_event_dispatcher.h"
#include "zedui/window/window.h"
#include "zedui/window/window_tree_host.h"

namespace zedui {

WindowEventDispatcher::WindowEventDispatcher(WindowTreeHost* host)
    : host_(host) {}

EventTarget* WindowEventDispatcher::GetRootForEvent(Event* event) {

}

Window* WindowEventDispatcher::window() {
  return host_->window();
}

const Window* WindowEventDispatcher::window() const {
  return host_->window();
}

} // namespace zedui