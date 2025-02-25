#ifndef TASK_RUNNER_H_
#define TASK_RUNNER_H_

#include <windows.h>

#include <chrono>
#include <deque>
#include <functional>
#include <memory>
#include <mutex>
#include <queue>
#include <variant>


#include "zedbase/macros.h"
#include "zedbase/task_runner_window.h"
#include "zedbase/time_delta.h"
#include "zedbase/time_point.h"

namespace zedbase {

class TaskRunner : public TaskRunnerWindow::Delegate {
 public:
  using TaskTimePoint = std::chrono::steady_clock::time_point;
  using TaskClosure = std::function<void()>;

  TaskRunner();

  virtual ~TaskRunner();
  virtual bool RunsTasksOnCurrentThread() const;
  void PostTask(TaskClosure task);
  void RunNowOrPostTask(TaskClosure task) {
    if (RunsTasksOnCurrentThread()) {
      task();
    } else {
      PostTask(std::move(task));
    }
  }
  void PostDelayedTask(TaskClosure task, const int64_t delay_ms);

  std::chrono::nanoseconds ProcessTasks();

 private:
  struct Task {
    uint64_t order;
    TaskTimePoint fire_time;
    TaskClosure closure;
    struct Comparer {
      bool operator()(const Task& a, const Task& b) {
        if (a.fire_time == b.fire_time) {
          return a.order > b.order;
        }
        return a.fire_time > b.fire_time;
      }
    };
  };

  void EnqueueTask(Task task);
  virtual void WakeUp();
  virtual TaskTimePoint GetCurrentTimeForTask() const {
    return TaskTimePoint::clock::now();
  }

  std::mutex task_queue_mutex_;
  std::priority_queue<Task, std::deque<Task>, Task::Comparer> task_queue_;
  DWORD main_thread_id_;
  std::shared_ptr<TaskRunnerWindow> task_runner_window_;

  ZED_DISALLOW_COPY_AND_ASSIGN(TaskRunner);
};

}  // namespace zedbase

#endif  // TASK_RUNNER_H_