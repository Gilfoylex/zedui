#pragma once

#include "zedbase/time/time_point.h"

namespace zedbase {

class Wakeable {
 public:
  virtual ~Wakeable() {}

  virtual void WakeUp(TimePoint time_point) = 0;
};

}  // namespace zedbase