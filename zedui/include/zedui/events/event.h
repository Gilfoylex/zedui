#pragma once
#include "zedbase/time/time_point.h"
#include "zedui/events/event_type.h"
#include "zedui/geometry/point.h"

namespace zedui {
class CancelModeEvent;
class LocatedEvent;
class MouseEvent;
class EventTarget;

class Event {
 public:
  virtual ~Event() = default;

  const zedbase::TimePoint time_stamp() const { return time_stamp_; }
  EventTarget* target() const { return target_; }
  void set_target(EventTarget* target) { target_ = target; }
  void set_time_stamp(zedbase::TimePoint time) { time_stamp_ = time; }

  bool IsMouseEvent() const {
    return type_ == EventType::kMousePressed ||
           type_ == EventType::kMouseDragged ||
           type_ == EventType::kMouseReleased ||
           type_ == EventType::kMouseMoved ||
           type_ == EventType::kMouseEntered ||
           type_ == EventType::kMouseExited ||
           type_ == EventType::kMousewheel ||
           type_ == EventType::kMouseCaptureChanged;
  }

  bool IsCancelModeEvent() const { return type_ == EventType::kCancelMode; }

  bool IsLocatedEvent() const {
    return IsMouseEvent() || type_ == EventType::kDropTargetEvent;
  }
  CancelModeEvent* AsCancelModeEvent();
  const CancelModeEvent* AsCancelModeEvent() const;
  MouseEvent* AsMouseEvent();
  const MouseEvent* AsMouseEvent() const;
  LocatedEvent* AsLocatedEvent();
  const LocatedEvent* AsLocatedEvent() const;

  void set_cancelable(bool cancelable) { cancelable_ = cancelable; }
  bool cancelable() const { return cancelable_; }
  
  bool handled() const { return handled_; }
  bool stopped() const { return stopped_; }
  void SetHandled(){
    handled_ = true;
  }
  
  void StopPropagation() {
    stopped_ = true;
  }

 protected:
  Event(EventType type, zedbase::TimePoint time_stamp);

  EventType type_;
  zedbase::TimePoint time_stamp_;
  bool cancelable_ = true;
  bool handled_ = false;
  bool stopped_;
  EventTarget* target_ = nullptr;
};

class CancelModeEvent : public Event {
 public:
  CancelModeEvent();
  ~CancelModeEvent() = default;
};

class LocatedEvent : public Event {
 protected:
  Point location_;
  Point root_location_;
};

class MouseEvent : public LocatedEvent {};

}  // namespace zedui