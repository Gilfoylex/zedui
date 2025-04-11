#include "zedbase/logging.h"
#include "zedbase/timer/timer.h"

namespace zedbase {
namespace internal {

bool DelayTimerBase::IsRunning() const {
  return running_;
}

void DelayTimerBase::SetTaskRunner(
    zedbase::RefPtr<zedbase::TaskRunner> task_runner) {
  ZED_DCHECK(task_runner);
  task_runner_ = task_runner;
}

void DelayTimerBase::StartInternal(TimeDelta delay) {
  delay_ = delay;
  ScheduleNewTask(delay);
}

TimeDelta DelayTimerBase::GetCurrentDelay() const {
  return delay_;
}

void DelayTimerBase::ScheduleNewTask(TimeDelta delay) {
  ZED_DCHECK(task_runner_);

  if (!timer_callback_) {
    timer_callback_ = std::bind(&DelayTimerBase::OnTaskInvoked, this);
  }

  task_runner_->PostDelayedTask(timer_callback_, delay);
}

void DelayTimerBase::OnTaskInvoked() {
  ZED_DCHECK(running_);
  RunUserTask();
}

}  // namespace internal

ThreadTimer::ThreadTimer() {}

ThreadTimer::~ThreadTimer() {
  Stop();
}

void ThreadTimer::Start(TimeDelta interval, const closure& user_task) {
  if (running_)
    Stop();
  running_ = true;
  thread_ = std::make_unique<zedbase::Thread>("timer_thread");
  user_task_ = user_task;
  SetTaskRunner(thread_->GetTaskRunner());
  StartInternal(interval);
}

void ThreadTimer::Stop() {
  if (!running_)
    return;

  running_ = false;
  thread_->Join();
  thread_.reset();
}

void ThreadTimer::RunUserTask() {
  zedbase::closure task = user_task_;
  ScheduleNewTask(GetCurrentDelay());
  task();
}

}  // namespace zedbase