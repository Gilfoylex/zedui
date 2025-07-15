#include "zedbase/task_source.h"

namespace zedbase {
TaskSource::TaskSource(TaskQueueId task_queue_id)
    : task_queue_id_(task_queue_id) {}

TaskSource::~TaskSource() {
  ShutDown();
}

void TaskSource::ShutDown() {
  task_queue_ = {};
}

void TaskSource::RegisterTask(const DelayedTask& task) {
  task_queue_.push(task);
}

void TaskSource::PopTask() {
  task_queue_.pop();
}

size_t TaskSource::GetNumPendingTasks() const {
  return task_queue_.size();
}

bool TaskSource::IsEmpty() const {
  return GetNumPendingTasks() == 0;
}

TaskSource::TopTask TaskSource::Top() const {
  ZED_CHECK(!IsEmpty());
  const auto& top = task_queue_.top();
  return {
      .task_queue_id = task_queue_id_,
      .task = top,
  };
}

}  // namespace zedbase