#pragma once

#include <windows.h>

#include <deque>
#include <memory>
#include <mutex>
#include <queue>
#include <variant>

#include "zedbase/closure.h"
#include "zedbase/macros.h"
#include "zedbase/time/time_delta.h"
#include "zedbase/time/time_point.h"
#include "zedui/utils/ui_task_runner_window.h"

namespace zedui {

// A custom task runner that integrates with user32 GetMessage semantics so
// that host app can own its own message loop and flutter still gets to process
// tasks on a timely basis.

class UITaskRunner : public UITaskRunnerWindow::Delegate {
 public:
  UITaskRunner();

  virtual ~UITaskRunner();
  virtual bool RunsTasksOnCurrentThread() const;
  void PostTask(zedbase::closure task);
  void RunNowOrPostTask(zedbase::closure task) {
    if (RunsTasksOnCurrentThread()) {
      task();
    } else {
      PostTask(std::move(task));
    }
  }
  void PostDelayedTask(zedbase::closure task, const int64_t delay_ms);

  zedbase::TimeDelta ProcessTasks() override;

 private:
  struct Task {
    uint64_t order;
    zedbase::TimePoint fire_time;
    zedbase::closure closure;
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
  virtual zedbase::TimePoint GetCurrentTimeForTask() const {
    return zedbase::TimePoint::Now();
  }

  std::mutex task_queue_mutex_;
  std::priority_queue<Task, std::deque<Task>, Task::Comparer> task_queue_;
  DWORD main_thread_id_;
  std::shared_ptr<UITaskRunnerWindow> task_runner_window_;

  ZED_DISALLOW_COPY_AND_ASSIGN(UITaskRunner);
};

}  // namespace zedui