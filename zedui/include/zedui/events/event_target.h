#pragma once
#include <memory>
#include <vector>
#include "zedui/events/event.h"
#include "zedui/events/event_handler.h"

namespace zedui {
class EventDispatcher;
class EventTarget {
 public:
  virtual ~EventTarget() = default;
  virtual EventTarget* GetParentTarget() const = 0;

  void AddPreTargetHandler(EventHandler* handler);
  void RemovePreTargetHandler(EventHandler* handler);
  void AddPostTargetHandler(EventHandler* handler);
  void RemovePostTargetHandler(EventHandler* handler);
  virtual EventTargeter* GetEventTargeter() = 0;

 protected:
  EventHandler* target_handler() { return target_handler_; }

 private:
  friend class EventDispatcher;
  EventHandler* target_handler_ = nullptr;
  EventHandlerList pre_target_list_;
  EventHandlerList post_target_list_;

  void GetPreTargetHandlers(EventHandlerList* list);
  void GetPostTargetHandlers(EventHandlerList* list);
};

}  // namespace zedui