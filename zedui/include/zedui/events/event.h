#pragma once
#include "zedbase/time/time_point.h"
#include "zedui/events/event_type.h"
#include "zedui/geometry/point.h"

namespace zedui {
class CancelModeEvent;
class LocatedEvent;
class MouseEvent;

class Event {
 public:
  virtual ~Event() = default;

  const zedbase::TimePoint GetTimeStamp() const { return timestamp_; }

  void SetTimeStamp(zedbase::TimePoint time_stamp) { timestamp_ = time_stamp; }

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

 protected:
  Event(EventType type, zedbase::TimePoint time_stamp);

 private:
  EventType type_;
  zedbase::TimePoint timestamp_;
  bool cancelasble_ = true;
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