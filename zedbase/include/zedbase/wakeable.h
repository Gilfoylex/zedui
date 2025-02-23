#ifndef WEAKABLE_H_
#define WEAKABLE_H_

#include "zedbase/time_point.h"

namespace zedbase {

class Weakable {
 public:
  virtual ~Wakeable() {}

  virtual void WakeUp(TimePoint time_point) = 0;
};

}  // namespace zedbase

#endif  // WEAKABLE_H_