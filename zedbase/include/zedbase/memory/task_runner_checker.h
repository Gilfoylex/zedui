#pragma once

#include "zedbase/message_loop.h"
#include "zedbase/task_runner.h"

namespace zedbase {
class TaskRunnerChecker final {
 public:
  TaskRunnerChecker();

  ~TaskRunnerChecker();

  bool RunsOnCreationTaskRunner() const;

  static bool RunsOnTheSameThread(TaskQueueId queue_a, TaskQueueId queue_b);

 private:
  TaskQueueId initialized_queue_id_;

  TaskQueueId InitTaskQueueId();
};

#if !defined(NDEBUG)
#define ZED_DECLARE_TASK_RUNNER_CHECKER(c) zedbase::TaskRunnerChecker c
#define ZED_DCHECK_TASK_RUNNER_IS_CURRENT(c) \
  ZED_DCHECK((c).RunsOnCreationTaskRunner())
#else
#define ZED_DECLARE_TASK_RUNNER_CHECKER(c)
#define ZED_DCHECK_TASK_RUNNER_IS_CURRENT(c) ((void)0)
#endif

}  // namespace zedbase