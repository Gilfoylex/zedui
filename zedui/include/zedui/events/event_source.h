#pragma once

namespace zedui {
class Event;
class EventSink;
class EventSource {
 public:
  virtual ~EventSource() = default;
  virtual EventSink* GetEventSink() = 0;
};

}  // namespace zedui