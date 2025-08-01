#include "zedbase/auto_reset.h"
#include "zedbase/logging.h"

#include "zedui/events/event_dispatcher.h"
#include "zedui/events/event_target.h"

namespace zedui {

EventDispatcherDelegate::EventDispatcherDelegate() : dispatcher_(nullptr) {}

EventDispatcherDelegate::~EventDispatcherDelegate() {
  if (dispatcher_)
    dispatcher_->OnDispatcherDelegateDestroyed();
}

void EventDispatcherDelegate::DispatchEvent(EventTarget* target, Event* event) {
  ZED_CHECK(target);

  PreDispatchEvent(target, event);
  if (!event->handled()) {
    DispatchEventToTarget(target, event);
  }
  PostDispatchEvent(target, *event);
}

void EventDispatcherDelegate::PreDispatchEvent(EventTarget* target,
                                               Event* event) {}

void EventDispatcherDelegate::PostDispatchEvent(EventTarget* target,
                                                const Event& event) {}

EventDispatcher::EventDispatcher(EventDispatcherDelegate* delegate)
    : delegate_(delegate) {}

EventDispatcher::~EventDispatcher() {
  // |handler_list_| must be empty, otherwise this has been added to an
  // EventHandler that will callback to this when destroyed.
  ZED_CHECK(handler_list_.empty());
}

void EventDispatcher::ProcessEvent(EventTarget* target, Event* event) {
  if (!target) {
    return;
  }

  Event::DispatcherApi dispatcher_api(event);
  dispatcher_api.set_target(target);

  handler_list_.clear();
  target->GetPreTargetHandlers(&handler_list_);
  DispatchEventToEventHandlers(&handler_list_, event);
  ZED_CHECK(handler_list_.empty());
  if (event->handled())
    return;

  if (delegate_ && delegate_->CanDispatchToTarget(target) &&
      target->target_handler()) {
    DispatchEvent(target->target_handler(), event);
    if (event->handled())
      return;
  }

  if (!delegate_ || !delegate_->CanDispatchToTarget(target))
    return;

  target->GetPostTargetHandlers(&handler_list_);
  DispatchEventToEventHandlers(&handler_list_, event);
}

void EventDispatcher::OnDispatcherDelegateDestroyed() {
  delegate_ = nullptr;
}

void EventDispatcher::DispatchEventToEventHandlers(EventHandlerList* list,
                                                   Event* event) {
  for (EventHandler* handler : *list) {
    handler->dispatchers_.push(this);
  }

  while (!list->empty()) {
    EventHandler* handler = (*list->begin());
    ZED_CHECK(handler->dispatchers_.top() == this);
    handler->dispatchers_.pop();
    list->erase(list->begin());
    if (delegate_) {
      DispatchEvent(handler, event);
    }
  }
}

void EventDispatcher::DispatchEvent(EventHandler* handler, Event* event) {
  if (!delegate_->CanDispatchToTarget(event->target())) {
    return;
  }

  zedbase::AutoReset<Event*> event_reset(&current_event_, event);
  handler->OnEvent(event);
}

}  // namespace zedui