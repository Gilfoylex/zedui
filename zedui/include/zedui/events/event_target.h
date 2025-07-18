#pragma once
#include <memory>
#include "zedui/events/event.h"

namespace zedui {
class EventTarget {
 public:
  virtual ~EventTarget() = default;
  virtual bool CanAcceptEvent(const Event& event) = 0;
  virtual EventTarget* FindTargetForEvent(const Event& event) = 0;
  virtual EventTarget* GetParentTarget() = 0;
};

}  // namespace zedui