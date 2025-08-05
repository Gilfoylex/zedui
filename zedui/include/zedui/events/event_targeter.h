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
  virtual EventTarget* FindNextBestTarget(EventTarget* previous_target,
                                          Event* event) = 0;

  virtual EventSink* GetNewEventSinkForEvent(const EventTarget* current_root,
                                             EventTarget* target,
                                             Event* in_out_event);

 private:
  friend class EventProcessor;

  zedbase::WeakPtr<EventTargeter> GetWeakPtr() {
    return weak_ptr_factory_.GetWeakPtr();
  }

  zedbase::WeakPtrFactory<EventTargeter> weak_ptr_factory_{this};
};
}  // namespace zedui