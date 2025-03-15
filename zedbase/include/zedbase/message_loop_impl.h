// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ZEDBASE_MESSAGE_LOOP_IMPL_H_
#define ZEDBASE_MESSAGE_LOOP_IMPL_H_

#include <atomic>
#include <deque>
#include <map>
#include <mutex>
#include <queue>
#include <utility>

#include "zedbase/closure.h"
#include "zedbase/delayed_task.h"
#include "zedbase/macros.h"
#include "zedbase/memory/ref_counted.h"
#include "zedbase/message_loop.h"
#include "zedbase/message_loop_task_queues.h"
#include "zedbase/time/time_point.h"
#include "zedbase/wakeable.h"

namespace zedbase {

/// An abstract class that represents the differences in implementation of a \p
/// fml::MessageLoop depending on the platform.
/// \see fml::MessageLoop
/// \see fml::MessageLoopAndroid
/// \see fml::MessageLoopDarwin
class MessageLoopImpl : public Wakeable,
                        public zedbase::RefCountedThreadSafe<MessageLoopImpl> {
 public:
  static zedbase::RefPtr<MessageLoopImpl> Create();

  virtual ~MessageLoopImpl();

  virtual void Run() = 0;

  virtual void Terminate() = 0;

  void PostTask(const zedbase::closure& task, zedbase::TimePoint target_time);

  void AddTaskObserver(intptr_t key, const zedbase::closure& callback);

  void RemoveTaskObserver(intptr_t key);

  void DoRun();

  void DoTerminate();

  virtual TaskQueueId GetTaskQueueId() const;

 protected:
  // Exposed for the embedder shell which allows clients to poll for events
  // instead of dedicating a thread to the message loop.
  friend class MessageLoop;

  void RunExpiredTasksNow();

  void RunSingleExpiredTaskNow();

 protected:
  MessageLoopImpl();

 private:
  zedbase::MessageLoopTaskQueues* task_queue_;
  TaskQueueId queue_id_;

  std::atomic_bool terminated_;

  void FlushTasks(FlushType type);

  ZED_DISALLOW_COPY_AND_ASSIGN(MessageLoopImpl);
};

}  // namespace zedbase

#endif  // ZEDBASE_MESSAGE_LOOP_IMPL_H_
