#ifndef ZEDBASE_DELAYED_TASK_H_
#define ZEDBASE_DELAYED_TASK_H_

#include <queue>
#include "zedbase/closure.h"
#include "zedbase/task_source_grade.h"
#include "zedbase/time/time_point.h"

namespace zedbase {
class DelayedTask {
 public:
  DelayedTask(size_t order,
              const closure& task,
              TimePoint target_time,
              TaskSourceGrade task_source_grade);

  DelayedTask(const DelayedTask& other);

  ~DelayedTask();

  const closure& GetTask() const;

  TimePoint GetTargetTime() const;

  TaskSourceGrade GetTaskSourceGrade() const;

  bool operator>(const DelayedTask& other) const;

 private:
  size_t order_;
  closure task_;
  TimePoint target_time_;
  TaskSourceGrade task_source_grade_;
};

using DelayedTaskQueue = std::priority_queue<DelayedTask,
                                             std::deque<DelayedTask>,
                                             std::greater<DelayedTask>>;
}  // namespace zedbase

#endif  // ZEDBASE_DELAYED_TASK_H_