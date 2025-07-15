#pragma once

#include "zedbase/logging.h"

namespace zedbase {
/**
 * `MessageLoopTaskQueues` task dispatcher's internal task queue identifier.
 */
class TaskQueueId {
 public:
  /// Intializes a task queue with the given value as it's ID.
  explicit TaskQueueId(size_t value) : value_(value) {}

  operator size_t() const {  // NOLINT(google-explicit-constructor)
    return value_;
  }

 private:
  size_t value_ = 0;
};

}  // namespace zedbase