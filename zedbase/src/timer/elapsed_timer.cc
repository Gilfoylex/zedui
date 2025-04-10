#include "elapsed_timer.h"
#include "zedbase/timer/elapsed_timer.h"

namespace zedbase {
ElapsedTimer::ElapsedTimer() : begin_(TimePoint::Now()) {}

ElapsedTimer::ElapsedTimer(ElapsedTimer&& other) : begin_(other.begin_) {}

ElapsedTimer& ElapsedTimer::operator=(ElapsedTimer&& other) {
  if (this != &other) {
    begin_ = other.begin_;
  }
  return *this;
}

TimeDelta ElapsedTimer::Elapsed() const {
  return TimePoint::Now() - begin_;
}

TimePoint ElapsedTimer::Begin() const {
  return begin_;
}

void ElapsedTimer::Reset() {
  begin_ = TimePoint::Now();
}

}  // namespace zedbase
