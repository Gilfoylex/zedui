#include "zedui/events/event_processor.h"

namespace zedui {
EventProcessor::EventProcessor() = default;

EventProcessor::~EventProcessor() = default;

void EventProcessor::OnEventFromSource(Event* event) {
  zedbase::WeakPtr<EventProcessor> weak_this = weak_ptr_factory_.GetWeakPtr();
  ZED_CHECK(event->target());
  Event* event_to_dispatch = event;
}

void EventProcessor::OnEventProcessingStarted(Event* event) {}

void EventProcessor::OnEventProcessingFinished(Event* event) {}
}  // namespace zedui