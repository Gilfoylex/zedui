#include "zedbase/task_runner.h"
#include "zedbase/memory/task_runner_checker.h"

#include <utility>

#include "zedbase/logging.h"
#include "zedbase/message_loop.h"
#include "zedbase/message_loop_impl.h"
#include "zedbase/message_loop_task_queues.h"

namespace zedbase {
TaskRunner::TaskRunner(zedbase::RefPtr<MessageLoopImpl> loop)
    : loop_(std::move(loop)) {}

TaskRunner::~TaskRunner() = default;

void TaskRunner::PostTask(const zedbase::closure& task) {
  loop_->PostTask(task, zedbase::TimePoint::Now());
}

void TaskRunner::PostTaskForTime(const zedbase::closure& task,
                                 zedbase::TimePoint target_time) {
  loop_->PostTask(task, target_time);
}

void TaskRunner::PostDelayedTask(const zedbase::closure& task,
                                 zedbase::TimeDelta delay) {
  loop_->PostTask(task, zedbase::TimePoint::Now() + delay);
}

TaskQueueId TaskRunner::GetTaskQueueId() {
  ZED_DCHECK(loop_);
  return loop_->GetTaskQueueId();
}

bool TaskRunner::RunsTasksOnCurrentThread() {
  if (!zedbase::MessageLoop::IsInitializedForCurrentThread()) {
    return false;
  }

  const auto current_queue_id = MessageLoop::GetCurrentTaskQueueId();
  const auto loop_queue_id = loop_->GetTaskQueueId();

  return TaskRunnerChecker::RunsOnTheSameThread(current_queue_id,
                                                loop_queue_id);
}

// static
void TaskRunner::RunNowOrPostTask(
    const zedbase::RefPtr<zedbase::TaskRunner>& runner,
    const zedbase::closure& task) {
  ZED_DCHECK(runner);
  if (runner->RunsTasksOnCurrentThread()) {
    task();
  } else {
    runner->PostTask(task);
  }
}

// static
void TaskRunner::RunNowAndFlushMessages(
    const zedbase::RefPtr<zedbase::TaskRunner>& runner,
    const zedbase::closure& task) {
  ZED_DCHECK(runner);
  if (runner->RunsTasksOnCurrentThread()) {
    task();
    // Post an empty task to make the UI message loop run its task observers.
    // The observers will execute any Dart microtasks queued by the platform
    // message handler.
    runner->PostTask([] {});
  } else {
    runner->PostTask(task);
  }
}

}  // namespace zedbase