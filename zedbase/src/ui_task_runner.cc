#include "zedbase/ui_task_runner.h"

#include <atomic>
#include <utility>

namespace zedbase {

UITaskRunner::UITaskRunner() {
  main_thread_id_ = GetCurrentThreadId();
  task_runner_window_ = TaskRunnerWindow::GetSharedInstance();
  task_runner_window_->AddDelegate(this);
}

UITaskRunner::~UITaskRunner() {
  task_runner_window_->RemoveDelegate(this);
}

void UITaskRunner::PostDelayedTask(TaskClosure task, const int64_t delay_ms) {
  Task delayed_task;
  delayed_task.fire_time =
      GetCurrentTimeForTask() + std::chrono::milliseconds(delay_ms);
  delayed_task.closure = std::move(task);
  EnqueueTask(std::move(delayed_task));
}

std::chrono::nanoseconds UITaskRunner::ProcessTasks() {
  const TaskTimePoint now = GetCurrentTimeForTask();

  std::vector<Task> expired_tasks;

  // Process expired tasks.
  {
    std::lock_guard<std::mutex> lock(task_queue_mutex_);
    while (!task_queue_.empty()) {
      const auto& top = task_queue_.top();
      // If this task (and all tasks after this) has not yet expired, there is
      // nothing more to do. Quit iterating.
      if (top.fire_time > now) {
        break;
      }

      // Make a record of the expired task. Do NOT service the task here
      // because we are still holding onto the task queue mutex. We don't want
      // other threads to block on posting tasks onto this thread till we are
      // done processing expired tasks.
      expired_tasks.push_back(task_queue_.top());

      // Remove the tasks from the delayed tasks queue.
      task_queue_.pop();
    }
  }

  // Fire expired tasks.
  {
    // Flushing tasks here without holing onto the task queue mutex.
    for (const auto& task : expired_tasks) {
      if (task.closure) {
        task.closure();
      }
    }
  }

  // Calculate duration to sleep for on next iteration.
  {
    std::lock_guard<std::mutex> lock(task_queue_mutex_);
    const auto next_wake = task_queue_.empty() ? TaskTimePoint::max()
                                               : task_queue_.top().fire_time;

    return std::min(next_wake - now, std::chrono::nanoseconds::max());
  }
}

void UITaskRunner::PostTask(TaskClosure closure) {
  Task task;
  task.fire_time = GetCurrentTimeForTask();
  task.closure = std::move(closure);
  EnqueueTask(std::move(task));
}

void UITaskRunner::EnqueueTask(Task task) {
  static std::atomic_uint64_t sGlobalTaskOrder(0);

  task.order = ++sGlobalTaskOrder;
  {
    std::lock_guard<std::mutex> lock(task_queue_mutex_);
    task_queue_.push(task);

    // Make sure the queue mutex is unlocked before waking up the loop. In case
    // the wake causes this thread to be descheduled for the primary thread to
    // process tasks, the acquisition of the lock on that thread while holding
    // the lock here momentarily till the end of the scope is a pessimization.
  }

  WakeUp();
}

bool UITaskRunner::RunsTasksOnCurrentThread() const {
  return GetCurrentThreadId() == main_thread_id_;
}

void UITaskRunner::WakeUp() {
  task_runner_window_->WakeUp();
}

}  // namespace zedbase