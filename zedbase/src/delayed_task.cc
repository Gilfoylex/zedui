#include "zedbase/delayed_task.h"

namespace zedbase {

DelayedTask::DelayedTask(size_t order,
                         const closure& task,
                         TimePoint target_time)
    : order_(order), task_(task), target_time_(target_time) {}

DelayedTask::~DelayedTask() = default;

DelayedTask::DelayedTask(const DelayedTask& other) = default;

const closure& DelayedTask::GetTask() const {
  return task_;
}

TimePoint DelayedTask::GetTargetTime() const {
  return target_time_;
}

bool DelayedTask::operator>(const DelayedTask& other) const {
  if (target_time_ == other.target_time_) {
    return order_ > other.order_;
  }
  return target_time_ > other.target_time_;
}

}  // namespace zedbase