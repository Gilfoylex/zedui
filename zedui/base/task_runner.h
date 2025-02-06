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


#include "macros.h"
#include "task_runner_window.h"


namespace zedui {

typedef struct _ZedUiTaskRunner* ZedUiTaskRunner;

typedef struct {
  ZedUiTaskRunner runner;
  uint64_t task;
} ZedUiTask;

typedef uint64_t (*CurrentTimeProc)();

class TaskRunner : public TaskRunnerWindow::Delegate {
 public:
  using TaskTimePoint = std::chrono::steady_clock::time_point;
  using TaskExpiredCallback = std::function<void(const ZedUiTask*)>;
  using TaskClosure = std::function<void()>;

  TaskRunner(CurrentTimeProc get_current_time,
             const TaskExpiredCallback& on_task_expired);

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

  std::chrono::nanoseconds ProcessTasks();

 private:
  typedef std::variant<ZedUiTask, TaskClosure> TaskVariant;
  struct Task {
    uint64_t order;
    TaskTimePoint fire_time;
    TaskVariant variant;
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

  CurrentTimeProc get_current_time_;
  TaskExpiredCallback on_task_expired_;
  std::mutex task_queue_mutex_;
  std::priority_queue<Task, std::deque<Task>, Task::Comparer> task_queue_;
  DWORD main_thread_id_;
  std::shared_ptr<TaskRunnerWindow> task_runner_window_;

  ZEDUI_DISALLOW_COPY_AND_ASSIGN(TaskRunner);
};

}  // namespace zedui

#endif  // TASK_RUNNER_H_