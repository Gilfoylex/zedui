#pragma once

#include "zedbase/closure.h"
#include "zedbase/macros.h"
#include "zedbase/memory/ref_ptr.h"
#include "zedbase/task_runner.h"
#include "zedbase/thread.h"
#include "zedbase/time/time_delta.h"

#include <atomic>
#include <memory>

namespace zedbase {
namespace internal {
class DelayTimerBase {
 public:
  DelayTimerBase() = default;
  virtual ~DelayTimerBase() = default;
  bool IsRunning() const;
  virtual void Start(TimeDelta interval, const closure& callback) = 0;
  virtual void Stop() = 0;

 protected:
  void SetTaskRunner(zedbase::RefPtr<zedbase::TaskRunner> task_runner);
  void StartInternal(TimeDelta delay);
  TimeDelta GetCurrentDelay() const;
  void ScheduleNewTask(TimeDelta delay);
  virtual void RunUserTask() = 0;

 private:
  void OnTaskInvoked();

 protected:
  std::atomic_bool running_;

 private:
  zedbase::RefPtr<zedbase::TaskRunner> task_runner_;
  zedbase::closure timer_callback_;
  zedbase::closure user_task_;
  zedbase::TimeDelta delay_;

  ZED_DISALLOW_COPY_ASSIGN_AND_MOVE(DelayTimerBase);
};
}  // namespace internal

class ThreadTimer final : public internal::DelayTimerBase {
 public:
  ThreadTimer();
  ~ThreadTimer() override;

  void Start(TimeDelta interval, const closure& user_task) override;
  void Stop() override;

 protected:
  void RunUserTask() override;

 private:
  std::unique_ptr<zedbase::Thread> thread_;
  zedbase::closure user_task_;

  ZED_DISALLOW_COPY_ASSIGN_AND_MOVE(ThreadTimer);
};

}  // namespace zedbase