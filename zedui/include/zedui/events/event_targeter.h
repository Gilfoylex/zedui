#pragma once
#include "zedbase/memory/weak_ptr.h"
namespace zedui {
class Event;
class EventTarget;
class EventSink;

class EventTargeter {
 public:
  EventTargeter() = default;
  virtual ~EventTargeter() = default;

  virtual EventTarget* FindTargetForEvent(EventTarget* root, Event* event) = 0;

 private:
  friend class EventProcessor;

  zedbase::WeakPtr<EventTargeter> GetWeakPtr() {
    return weak_ptr_factory_.GetWeakPtr();
  }

  zedbase::WeakPtrFactory<EventTargeter> weak_ptr_factory_{this};
};
}  // namespace zedui