#ifndef ZEDBASE_TIMER_ELAPSED_TIMER_H_
#define ZEDBASE_TIMER_ELAPSED_TIMER_H_

#include "zedbase/macros.h"
#include "zedbase/time/time_point.h"

namespace zedbase {
class ElapsedTimer {
 public:
  ElapsedTimer();
  ElapsedTimer(ElapsedTimer&& other);
  ElapsedTimer& operator=(ElapsedTimer&& other);

  TimeDelta Elapsed() const;
  TimePoint Begin() const;

 private:
  TimePoint begin_;

  ZED_DISALLOW_COPY_AND_ASSIGN(ElapsedTimer);
};
}  // namespace zedbase

#endif  // ZEDBASE_TIMER_ELAPSED_TIMER_H_