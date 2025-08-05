#pragma once

#include "zedui/events/event_dispatcher.h"
#include "zedui/events/event_sink.h"

#include "zedbase/memory/weak_ptr.h"

namespace zedui {

class EventProcessor : public EventDispatcherDelegate, public EventSink {
 public:
  EventProcessor();
  ~EventProcessor() override;

  // EventSink overrides
  void OnEventFromSource(Event* event) override;

  // Returns the EventTarget with the right EventTargeter that we should use for
  // dispatching this |event|.
  virtual EventTarget* GetRootForEvent(Event* event) = 0;
  // If the root target returned by GetRootForEvent() does not have a
  // targeter set, then the default targeter is used to find the target.
  virtual EventTargeter* GetDefaultEventTargeter() = 0;

 protected:
  // Invoked at the start of processing, before an EventTargeter is used to
  // find the target of the event. If processing should not take place, marks
  // |event| as handled. Otherwise updates |event| so that the targeter can
  // operate correctly (e.g., it can be used to update the location of the
  // event when dispatching from an EventSource in high-DPI) and updates any
  // members in the event processor as necessary.
  virtual void OnEventProcessingStarted(Event* event);

  // Invoked when the processing of |event| has finished (i.e., when no further
  // dispatching of |event| will be performed by this EventProcessor). Note
  // that the last target to which |event| was dispatched may have been
  // destroyed.
  virtual void OnEventProcessingFinished(Event* event);

 private:
  zedbase::WeakPtrFactory<EventProcessor> weak_ptr_factory_{this};
};
}  // namespace zedui