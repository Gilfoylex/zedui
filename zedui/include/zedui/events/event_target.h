#pragma once
#include <memory>
#include <vector>
#include "zedui/events/event.h"
#include "zedui/events/event_handler.h"

namespace zedui {
class EventDispatcher;
class EventTargeter;
class EventTarget {
 public:
  virtual ~EventTarget() = default;

  // Priority levels for PreTargetHandlers.
  enum class Priority {
    // The Accessibility level is the highest, and gets events before
    // other priority levels. This allows accessibility features to
    // modify events directly from the user. Note that Ash accessibility
    // features should not use this directly, but instead should go
    // through ash::Shell::AddAccessibilityEventHandler to allow for
    // fine-grained control of ordering amongst themselves.
    kAccessibility,

    // System priority EventHandlers get events before default level, and
    // should be used for drag and drop, menus, etc.
    kSystem,

    // The default level should be used by most EventHandlers.
    kDefault,
  };

  virtual bool CanAcceptEvent(const Event& event) = 0;
  virtual EventTarget* GetParentTarget() const = 0;
  virtual EventTargeter* GetEventTargeter() = 0;

  void AddPreTargetHandler(EventHandler* handler);
  void AddPreTargetHandler(EventHandler* handler, Priority priority);
  void RemovePreTargetHandler(EventHandler* handler);
  void AddPostTargetHandler(EventHandler* handler);
  void RemovePostTargetHandler(EventHandler* handler);
  EventHandler* SetTargetHandler(EventHandler* target_handler);
  bool IsPreTargetListEmpty() const;

  bool HasTargetHandler() const { return target_handler_ != nullptr; }

 protected:
  EventHandler* target_handler() { return target_handler_; }

 private:
  friend class EventDispatcher;

  struct PrioritizedHandler {
    EventHandler* handler = nullptr;
    Priority priority = Priority::kDefault;

    bool operator<(const PrioritizedHandler& ph) const {
      return priority < ph.priority;
    }
  };
  using EventHandlerPriorityList = std::vector<PrioritizedHandler>;
  void GetPreTargetHandlers(EventHandlerList* list);
  void GetPostTargetHandlers(EventHandlerList* list);

  EventHandler* target_handler_ = nullptr;
  EventHandlerPriorityList pre_target_list_;
  EventHandlerList post_target_list_;  
};

}  // namespace zedui