#include "zedui/events/event_targeter.h"

namespace zedui {
EventSink* EventTargeter::GetNewEventSinkForEvent(
    const EventTarget* current_root,
    EventTarget* target,
    Event* in_out_event) {
  return nullptr;
}
}  // namespace zedui