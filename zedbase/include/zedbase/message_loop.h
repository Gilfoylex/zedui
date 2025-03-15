#ifndef MESSAGE_LOOP_H_
#define MESSAGE_LOOP_H_

#include "zedbase/macros.h"
#include "zedbase/task_runner.h"

namespace zedbase {

class TaskRunner;
class MessageLoopImpl;
/// An event loop associated with a thread.
///
/// This class is the generic front-end to the MessageLoop, differences in
/// implementation based on the running platform are in the subclasses of
/// flutter::MessageLoopImpl (ex flutter::MessageLoopAndroid).
///
/// For scheduling events on the message loop see flutter::TaskRunner.
///
/// \see zedbase::TaskRunner
/// \see zedbase::MessageLoopImpl
/// \see zedbase::MessageLoopTaskQueues
/// \see zedbase::Wakeable
class MessageLoop {
 public:
  static MessageLoop& GetCurrent();

  void Run();

  void Terminate();

  void AddTaskObserver(intptr_t key, const zedbase::closure& callback);

  void RemoveTaskObserver(intptr_t key);

  zedbase::RefPtr<zedbase::TaskRunner> GetTaskRunner() const;

  // Exposed for the embedder shell which allows clients to poll for events
  // instead of dedicating a thread to the message loop.
  void RunExpiredTasksNow();

  static void EnsureInitializedForCurrentThread();

  /// Returns true if \p EnsureInitializedForCurrentThread has been called on
  /// this thread already.
  static bool IsInitializedForCurrentThread();

  ~MessageLoop();

  /// Gets the unique identifier for the TaskQueue associated with the current
  /// thread.
  /// \see fml::MessageLoopTaskQueues
  static TaskQueueId GetCurrentTaskQueueId();

 private:
  friend class TaskRunner;
  friend class MessageLoopImpl;

  zedbase::RefPtr<MessageLoopImpl> loop_;
  zedbase::RefPtr<zedbase::TaskRunner> task_runner_;

  MessageLoop();

  zedbase::RefPtr<MessageLoopImpl> GetLoopImpl() const;

  ZED_DISALLOW_COPY_AND_ASSIGN(MessageLoop);
};

}  // namespace zedbase

#endif  // MESSAGE_LOOP_H_