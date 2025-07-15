#include "zedbase/logging.h"
#include "zedbase/memory/task_runner_checker.h"

namespace zedbase {

TaskRunnerChecker::TaskRunnerChecker()
    : initialized_queue_id_(InitTaskQueueId()) {};

TaskRunnerChecker::~TaskRunnerChecker() = default;

bool TaskRunnerChecker::RunsOnCreationTaskRunner() const {
  ZED_CHECK(zedbase::MessageLoop::IsInitializedForCurrentThread());
  const auto current_queue_id = MessageLoop::GetCurrentTaskQueueId();
  if (RunsOnTheSameThread(current_queue_id, initialized_queue_id_)) {
    return true;
  }

  return false;
};

bool TaskRunnerChecker::RunsOnTheSameThread(TaskQueueId queue_a,
                                            TaskQueueId queue_b) {
  if (queue_a == queue_b) {
    return true;
  }

  return false;
};

TaskQueueId TaskRunnerChecker::InitTaskQueueId() {
  MessageLoop::EnsureInitializedForCurrentThread();
  return MessageLoop::GetCurrentTaskQueueId();
};

}  // namespace zedbase