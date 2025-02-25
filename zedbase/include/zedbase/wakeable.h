#ifndef WAKEABLE_H_
#define WAKEABLE_H_

#include "zedbase/time_point.h"

namespace zedbase {

class Wakeable {
 public:
  virtual ~Wakeable() {}

  virtual void WakeUp(TimePoint time_point) = 0;
};

}  // namespace zedbase

#endif  // WAKEABLE_H_