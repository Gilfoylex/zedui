#pragma once

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
  void Reset();

 private:
  TimePoint begin_;

  ZED_DISALLOW_COPY_AND_ASSIGN(ElapsedTimer);
};
}  // namespace zedbase