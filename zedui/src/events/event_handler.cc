#include "zedui/events/event.h"
#include "zedui/events/event_handler.h"

namespace zedui {

void EventHandler::OnEvent(Event* event) {
  if (event->IsMouseEvent()) {
    OnMouseEvent(event->AsMouseEvent());
  } else if (event->IsCancelModeEvent()) {
    OnCancelMode(event->AsCancelModeEvent());
  }
}
void EventHandler::OnCancelMode(CancelModeEvent* event) {}
void EventHandler::OnMouseEvent(MouseEvent* event) {}

}  // namespace zedui