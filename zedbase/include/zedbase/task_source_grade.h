#ifndef ZEDBASE_TASK_SOURCE_GRADE_H_
#define ZEDBASE_TASK_SOURCE_GRADE_H_

namespace zedbase {

/**
 * Categories of work dispatched to `MessageLoopTaskQueues` dispatcher. By
 * specifying the `TaskSourceGrade`, you indicate the task's importance to the
 * dispatcher.
 */
enum class TaskSourceGrade {
  /// This `TaskSourceGrade` indicates that a task is critical to user
  /// interaction.
  kUserInteraction,
  /// This `TaskSourceGrade` indicates that a task corresponds to servicing a
  /// dart event loop task. These aren't critical to user interaction.
  kDartEventLoop,
  /// The absence of a specialized `TaskSourceGrade`.
  kUnspecified,
};

} // namespace zedbase

#endif // ZEDBASE_TASK_SOURCE_GRADE_H_