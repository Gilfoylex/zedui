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

 private:
  zedbase::WeakPtrFactory<EventProcessor> weak_ptr_factory_{this};
};
}  // namespace zedui