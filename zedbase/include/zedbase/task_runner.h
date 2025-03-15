#ifndef ZEDBASE_TASK_RUNNER_H_
#define ZEDBASE_TASK_RUNNER_H_

#include "zedbase/closure.h"
#include "zedbase/macros.h"
#include "zedbase/memory/ref_counted.h"
#include "zedbase/memory/ref_ptr.h"
#include "zedbase/message_loop_task_queues.h"
#include "zedbase/time/time_point.h"


namespace zedbase {

class MessageLoopImpl;

/// An interface over the ability to schedule tasks on a \p TaskRunner.
class BasicTaskRunner {
 public:
  /// Schedules \p task to be executed on the TaskRunner's associated event
  /// loop.
  virtual void PostTask(const zedbase::closure& task) = 0;
};

/// The object for scheduling tasks on a \p fml::MessageLoop.
///
/// Typically there is one \p TaskRunner associated with each thread.  When one
/// wants to execute an operation on that thread they post a task to the
/// TaskRunner.
///
/// \see fml::MessageLoop
class TaskRunner : public zedbase::RefCountedThreadSafe<TaskRunner>,
                   public BasicTaskRunner {
 public:
  virtual ~TaskRunner();

  virtual void PostTask(const zedbase::closure& task) override;

  virtual void PostTaskForTime(const zedbase::closure& task,
                               zedbase::TimePoint target_time);

  /// Schedules a task to be run on the MessageLoop after the time \p delay has
  /// passed.
  /// \note There is latency between when the task is schedule and actually
  /// executed so that the actual execution time is: now + delay +
  /// message_loop_latency, where message_loop_latency is undefined and could be
  /// tens of milliseconds.
  virtual void PostDelayedTask(const zedbase::closure& task,
                               zedbase::TimeDelta delay);

  /// Returns \p true when the current executing thread's TaskRunner matches
  /// this instance.
  virtual bool RunsTasksOnCurrentThread();

  /// Returns the unique identifier associated with the TaskRunner.
  /// \see fml::MessageLoopTaskQueues
  ///
  /// Will be TaskQueueId::kInvalid for embedder supplied task runners
  /// that are not associated with a task queue.
  virtual TaskQueueId GetTaskQueueId();

  /// Executes the \p task directly if the TaskRunner \p runner is the
  /// TaskRunner associated with the current executing thread.
  static void RunNowOrPostTask(
      const zedbase::RefPtr<zedbase::TaskRunner>& runner,
      const zedbase::closure& task);

  /// Like RunNowOrPostTask, except that if the task can be immediately
  /// executed, an empty task will still be posted to the runner afterwards.
  ///
  /// This is used to ensure that messages posted to Dart from the platform
  /// thread always flush the Dart event loop.
  static void RunNowAndFlushMessages(
      const zedbase::RefPtr<zedbase::TaskRunner>& runner,
      const zedbase::closure& task);

 protected:
  explicit TaskRunner(zedbase::RefPtr<MessageLoopImpl> loop);

 private:
  zedbase::RefPtr<MessageLoopImpl> loop_;

  ZED_FRIEND_MAKE_REF_COUNTED(TaskRunner);
  ZED_FRIEND_REF_COUNTED_THREAD_SAFE(TaskRunner);
  ZED_DISALLOW_COPY_AND_ASSIGN(TaskRunner);
};

}  // namespace zedbase

#endif  // ZEDBASE_TASK_RUNNER_H_