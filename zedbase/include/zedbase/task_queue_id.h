#ifndef ZEBASE_TASK_QUEUE_ID_H_
#define ZEBASE_TASK_QUEUE_ID_H_

#include "zedbase/logging.h"

namespace zedbase {
/**
 * `MessageLoopTaskQueues` task dispatcher's internal task queue identifier.
 */
class TaskQueueId {
 public:
  /// This constant indicates whether a task queue has been subsumed by a task
  /// runner.
  static const size_t kUnmerged;

  /// Intializes a task queue with the given value as it's ID.
  explicit TaskQueueId(size_t value) : value_(value) {}

  operator size_t() const {  // NOLINT(google-explicit-constructor)
    return value_;
  }

 private:
  size_t value_ = kUnmerged;
};

}  // namespace zedbase

#endif  // ZEBASE_TASK_QUEUE_ID_H_