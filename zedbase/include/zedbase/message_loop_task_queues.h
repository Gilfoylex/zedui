#pragma once

#include <map>
#include <memory>
#include <mutex>
#include <set>
#include <vector>

#include "zedbase/closure.h"
#include "zedbase/delayed_task.h"
#include "zedbase/macros.h"
#include "zedbase/memory/ref_counted.h"
#include "zedbase/task_queue_id.h"
#include "zedbase/task_source.h"
#include "zedbase/wakeable.h"

namespace zedbase {

/// A collection of tasks and observers associated with one TaskQueue.
///
/// Often a TaskQueue has a one-to-one relationship with a fml::MessageLoop,
/// this isn't the case when TaskQueues are merged via
/// \p fml::MessageLoopTaskQueues::Merge.
class TaskQueueEntry {
 public:
  using TaskObservers = std::map<intptr_t, zedbase::closure>;
  Wakeable* wakeable;
  TaskObservers task_observers;
  std::unique_ptr<TaskSource> task_source;

  TaskQueueId created_for;

  explicit TaskQueueEntry(TaskQueueId created_for);

 private:
  ZED_DISALLOW_COPY_ASSIGN_AND_MOVE(TaskQueueEntry);
};

enum class FlushType {
  kSingle,
  kAll,
};

/// A singleton container for all tasks and observers associated with all
/// fml::MessageLoops.
///
/// This also wakes up the loop at the required times.
/// \see fml::MessageLoop
/// \see fml::Wakeable
class MessageLoopTaskQueues {
 public:
  // Lifecycle.

  static MessageLoopTaskQueues* GetInstance();

  TaskQueueId CreateTaskQueue();

  void Dispose(TaskQueueId queue_id);

  void DisposeTasks(TaskQueueId queue_id);

  // Tasks methods.

  void RegisterTask(TaskQueueId queue_id,
                    const closure& task,
                    TimePoint target_time);

  bool HasPendingTasks(TaskQueueId queue_id) const;

  closure GetNextTaskToRun(TaskQueueId queue_id, TimePoint from_time);

  size_t GetNumPendingTasks(TaskQueueId queue_id) const;

  // Observers methods.

  void AddTaskObserver(TaskQueueId queue_id,
                       intptr_t key,
                       const closure& callback);

  void RemoveTaskObserver(TaskQueueId queue_id, intptr_t key);

  std::vector<closure> GetObserversToNotify(TaskQueueId queue_id) const;

  void SetWakeable(TaskQueueId queue_id, Wakeable* wakeable);

 private:
  class MergedQueuesRunner;

  MessageLoopTaskQueues();

  ~MessageLoopTaskQueues();

  void WakeUpUnlocked(TaskQueueId queue_id, TimePoint time) const;

  bool HasPendingTasksUnlocked(TaskQueueId queue_id) const;

  TaskSource::TopTask PeekNextTaskUnlocked(TaskQueueId owner) const;

  TimePoint GetNextWakeTimeUnlocked(TaskQueueId queue_id) const;

  mutable std::mutex queue_mutex_;
  std::map<TaskQueueId, std::unique_ptr<TaskQueueEntry>> queue_entries_;

  size_t task_queue_id_counter_ = 0;

  std::atomic_int order_;

  ZED_DISALLOW_COPY_ASSIGN_AND_MOVE(MessageLoopTaskQueues);
};

}  // namespace zedbase