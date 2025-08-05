#include "zedbase/logging.h"
#include "zedui/events/event.h"

namespace zedui {

Event::Event(EventType type, zedbase::TimePoint time_stamp)
    : type_(type), time_stamp_(time_stamp) {}

CancelModeEvent* Event::AsCancelModeEvent() {
  ZED_CHECK(IsCancelModeEvent());
  return static_cast<CancelModeEvent*>(this);
}

const CancelModeEvent* Event::AsCancelModeEvent() const {
  ZED_CHECK(IsCancelModeEvent());
  return static_cast<const CancelModeEvent*>(this);
}

MouseEvent* Event::AsMouseEvent() {
  ZED_CHECK(IsMouseEvent());
  return static_cast<MouseEvent*>(this);
}
const MouseEvent* Event::AsMouseEvent() const {
  ZED_CHECK(IsMouseEvent());
  return static_cast<const MouseEvent*>(this);
}

LocatedEvent* Event::AsLocatedEvent() {
  ZED_CHECK(IsLocatedEvent());
  return static_cast<LocatedEvent*>(this);
}
const LocatedEvent* Event::AsLocatedEvent() const {
  ZED_CHECK(IsLocatedEvent());
  return static_cast<const LocatedEvent*>(this);
}

CancelModeEvent::CancelModeEvent()
    : Event(EventType::kCancelMode, zedbase::TimePoint()) {

}
}