// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "zedbase/message_loop_impl.h"

#include <algorithm>
#include <vector>

// #include "flutter/fml/build_config.h"
#include "zedbase/logging.h"

// #if FML_OS_MACOSX
// #include "flutter/fml/platform/darwin/message_loop_darwin.h"
// #elif FML_OS_ANDROID
// #include "flutter/fml/platform/android/message_loop_android.h"
// #elif OS_FUCHSIA
// #include "flutter/fml/platform/fuchsia/message_loop_fuchsia.h"
// #elif FML_OS_LINUX
// #include "flutter/fml/platform/linux/message_loop_linux.h"
// #elif FML_OS_WIN
#include "zedbase/platform/win/message_loop_win.h"
// #endif

namespace zedbase {

zedbase::RefPtr<MessageLoopImpl> MessageLoopImpl::Create() {
  // #if FML_OS_MACOSX
  //   return fml::MakeRefCounted<MessageLoopDarwin>();
  // #elif FML_OS_ANDROID
  //   return fml::MakeRefCounted<MessageLoopAndroid>();
  // #elif OS_FUCHSIA
  //   return fml::MakeRefCounted<MessageLoopFuchsia>();
  // #elif FML_OS_LINUX
  //   return fml::MakeRefCounted<MessageLoopLinux>();
  // #elif FML_OS_WIN
  return zedbase::MakeRefCounted<MessageLoopWin>();
  // #else
  //   return nullptr;
  // #endif
}

MessageLoopImpl::MessageLoopImpl()
    : task_queue_(MessageLoopTaskQueues::GetInstance()),
      queue_id_(task_queue_->CreateTaskQueue()),
      terminated_(false) {
  task_queue_->SetWakeable(queue_id_, this);
}

MessageLoopImpl::~MessageLoopImpl() {
  task_queue_->Dispose(queue_id_);
}

void MessageLoopImpl::PostTask(const zedbase::closure& task,
                               zedbase::TimePoint target_time) {
  ZED_DCHECK(task != nullptr);
  if (terminated_) {
    // If the message loop has already been terminated, PostTask should destruct
    // |task| synchronously within this function.
    return;
  }
  task_queue_->RegisterTask(queue_id_, task, target_time);
}

void MessageLoopImpl::AddTaskObserver(intptr_t key,
                                      const zedbase::closure& callback) {
  ZED_DCHECK(callback != nullptr);
  ZED_DCHECK(MessageLoop::GetCurrent().GetLoopImpl().get() == this)
      << "Message loop task observer must be added on the same thread as the "
         "loop.";
  if (callback != nullptr) {
    task_queue_->AddTaskObserver(queue_id_, key, callback);
  } else {
    ZED_LOG(ERROR) << "Tried to add a null TaskObserver.";
  }
}

void MessageLoopImpl::RemoveTaskObserver(intptr_t key) {
  ZED_DCHECK(MessageLoop::GetCurrent().GetLoopImpl().get() == this)
      << "Message loop task observer must be removed from the same thread as "
         "the loop.";
  task_queue_->RemoveTaskObserver(queue_id_, key);
}

void MessageLoopImpl::DoRun() {
  if (terminated_) {
    // Message loops may be run only once.
    return;
  }

  // Allow the implementation to do its thing.
  Run();

  // The loop may have been implicitly terminated. This can happen if the
  // implementation supports termination via platform specific APIs or just
  // error conditions. Set the terminated flag manually.
  terminated_ = true;

  // The message loop is shutting down. Check if there are expired tasks. This
  // is the last chance for expired tasks to be serviced. Make sure the
  // terminated flag is already set so we don't accrue additional tasks now.
  RunExpiredTasksNow();

  // When the message loop is in the process of shutting down, pending tasks
  // should be destructed on the message loop's thread. We have just returned
  // from the implementations |Run| method which we know is on the correct
  // thread. Drop all pending tasks on the floor.
  task_queue_->DisposeTasks(queue_id_);
}

void MessageLoopImpl::DoTerminate() {
  terminated_ = true;
  Terminate();
}

void MessageLoopImpl::FlushTasks(FlushType type) {
  const auto now = zedbase::TimePoint::Now();
  zedbase::closure invocation;
  do {
    invocation = task_queue_->GetNextTaskToRun(queue_id_, now);
    if (!invocation) {
      break;
    }
    invocation();
    std::vector<zedbase::closure> observers =
        task_queue_->GetObserversToNotify(queue_id_);
    for (const auto& observer : observers) {
      observer();
    }
    if (type == FlushType::kSingle) {
      break;
    }
  } while (invocation);
}

void MessageLoopImpl::RunExpiredTasksNow() {
  FlushTasks(FlushType::kAll);
}

void MessageLoopImpl::RunSingleExpiredTaskNow() {
  FlushTasks(FlushType::kSingle);
}

TaskQueueId MessageLoopImpl::GetTaskQueueId() const {
  return queue_id_;
}

}  // namespace zedbase
