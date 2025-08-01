#pragma once

#include <vector>
#include "zedui/events/event.h"
#include "zedui/events/event_handler.h"

namespace zedui {
class EventDispatcher;
class EventTarget;
class EventTargeter;
class EventDispatcherDelegate {
 public:
  EventDispatcherDelegate();
  virtual ~EventDispatcherDelegate();
  virtual EventTargeter* GetEventTargeter() const = 0;
  virtual bool CanDispatchToTarget(EventTarget* target) = 0;
  virtual void DispatchEvent(EventTarget* target, Event* event);

 protected:
  virtual void PreDispatchEvent(EventTarget* target, Event* event);
  virtual void PostDispatchEvent(EventTarget* target, const Event& event);

 private:
  void DispatchEventToTarget(EventTarget* target, Event* event);
  EventDispatcher* dispatcher_;
};

class EventDispatcher {
 public:
  explicit EventDispatcher(EventDispatcherDelegate* delegate);
  virtual ~EventDispatcher();
  void ProcessEvent(EventTarget* target, Event* event);

  const Event* current_event() const { return current_event_; }
  Event* current_event() { return current_event_; }

  void OnDispatcherDelegateDestroyed();

 private:
  void DispatchEventToEventHandlers(EventHandlerList* list, Event* event);
  void DispatchEvent(EventHandler* handler, Event* event);

  EventDispatcherDelegate* delegate_;
  EventHandlerList handler_list_;
  Event* current_event_ = nullptr;
};

}  // namespace zedui