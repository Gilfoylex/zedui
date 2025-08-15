// Generic implementation template for EventTarget pure virtual functions

#pragma once
#include "zedui/events/event_target.h"

namespace zedui {

// Base implementation template for EventTarget pure virtual functions
template <typename ParentType = EventTarget*, typename TargeterType = EventTargeter*>
class EventTargetImpl : public EventTarget {
 public:
  // Default implementation of CanAcceptEvent
  // Subclasses should override this with more specific logic if needed
  bool CanAcceptEvent(const Event& event) override {
    return true;  // By default, accept all events
  }

  // Default implementation of GetParentTarget
  // Requires setting a parent pointer or overriding in subclasses
  EventTarget* GetParentTarget() const override {
    return parent_target_;
  }

  // Default implementation of GetEventTargeter
  // Requires setting a targeter or overriding in subclasses
  EventTargeter* GetEventTargeter() override {
    return event_targeter_;
  }

 protected:
  // Setter methods for parent and targeter to support flexible configuration
  void SetParentTarget(ParentType parent) {
    parent_target_ = parent;
  }

  void SetEventTargeter(TargeterType targeter) {
    event_targeter_ = targeter;
  }

 private:
  ParentType parent_target_ = nullptr;
  TargeterType event_targeter_ = nullptr;
};

}  // namespace zedui
