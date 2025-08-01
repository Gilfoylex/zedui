#pragma once

namespace zedui {

class Event;
class EventSink {
 public:
  virtual ~EventSink() = default;
  virtual void OnEventFromSource(Event* event) = 0;
};

}  // namespace zedui
