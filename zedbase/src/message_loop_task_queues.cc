// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// #define FML_USED_ON_EMBEDDER

#include "zedbase/message_loop_task_queues.h"

#include <algorithm>
#include <iostream>
#include <memory>
#include <optional>

#include "zedbase/logging.h"
#include "zedbase/make_copyable.h"
#include "zedbase/task_source.h"

namespace zedbase {

TaskQueueEntry::TaskQueueEntry(TaskQueueId created_for_arg)
    : created_for(created_for_arg) {
  wakeable = nullptr;
  task_observers = TaskObservers();
  task_source = std::make_unique<TaskSource>(created_for);
}

MessageLoopTaskQueues* MessageLoopTaskQueues::GetInstance() {
  static MessageLoopTaskQueues* instance = new MessageLoopTaskQueues;
  return instance;
}

TaskQueueId MessageLoopTaskQueues::CreateTaskQueue() {
  std::lock_guard guard(queue_mutex_);
  TaskQueueId loop_id = TaskQueueId(task_queue_id_counter_);
  ++task_queue_id_counter_;
  queue_entries_[loop_id] = std::make_unique<TaskQueueEntry>(loop_id);
  return loop_id;
}

MessageLoopTaskQueues::MessageLoopTaskQueues() : order_(0) {}

MessageLoopTaskQueues::~MessageLoopTaskQueues() = default;

void MessageLoopTaskQueues::Dispose(TaskQueueId queue_id) {
  std::lock_guard guard(queue_mutex_);
  const auto& queue_entry = queue_entries_.at(queue_id);
  // Erase owner queue_id at last to avoid &subsumed_set from being invalid
  queue_entries_.erase(queue_id);
}

void MessageLoopTaskQueues::DisposeTasks(TaskQueueId queue_id) {
  std::lock_guard guard(queue_mutex_);
  const auto& queue_entry = queue_entries_.at(queue_id);
  queue_entry->task_source->ShutDown();
}

void MessageLoopTaskQueues::RegisterTask(TaskQueueId queue_id,
                                         const zedbase::closure& task,
                                         zedbase::TimePoint target_time) {
  std::lock_guard guard(queue_mutex_);
  size_t order = order_++;
  const auto& queue_entry = queue_entries_.at(queue_id);
  queue_entry->task_source->RegisterTask({order, task, target_time});
  TaskQueueId loop_to_wake = queue_id;
  if (HasPendingTasksUnlocked(loop_to_wake)) {
    WakeUpUnlocked(loop_to_wake, GetNextWakeTimeUnlocked(loop_to_wake));
  }
}

bool MessageLoopTaskQueues::HasPendingTasks(TaskQueueId queue_id) const {
  std::lock_guard guard(queue_mutex_);
  return HasPendingTasksUnlocked(queue_id);
}

zedbase::closure MessageLoopTaskQueues::GetNextTaskToRun(
    TaskQueueId queue_id,
    zedbase::TimePoint from_time) {
  std::lock_guard guard(queue_mutex_);
  if (!HasPendingTasksUnlocked(queue_id)) {
    return nullptr;
  }
  TaskSource::TopTask top = PeekNextTaskUnlocked(queue_id);

  if (!HasPendingTasksUnlocked(queue_id)) {
    WakeUpUnlocked(queue_id, zedbase::TimePoint::Max());
  } else {
    WakeUpUnlocked(queue_id, GetNextWakeTimeUnlocked(queue_id));
  }

  if (top.task.GetTargetTime() > from_time) {
    return nullptr;
  }
  zedbase::closure invocation = top.task.GetTask();
  queue_entries_.at(queue_id)->task_source->PopTask();
  return invocation;
}

void MessageLoopTaskQueues::WakeUpUnlocked(TaskQueueId queue_id,
                                           zedbase::TimePoint time) const {
  if (queue_entries_.at(queue_id)->wakeable) {
    queue_entries_.at(queue_id)->wakeable->WakeUp(time);
  }
}

size_t MessageLoopTaskQueues::GetNumPendingTasks(TaskQueueId queue_id) const {
  std::lock_guard guard(queue_mutex_);
  const auto& queue_entry = queue_entries_.at(queue_id);

  size_t total_tasks = 0;
  total_tasks += queue_entry->task_source->GetNumPendingTasks();
  return total_tasks;
}

void MessageLoopTaskQueues::AddTaskObserver(TaskQueueId queue_id,
                                            intptr_t key,
                                            const zedbase::closure& callback) {
  std::lock_guard guard(queue_mutex_);
  ZED_DCHECK(callback != nullptr) << "Observer callback must be non-null.";
  queue_entries_.at(queue_id)->task_observers[key] = callback;
}

void MessageLoopTaskQueues::RemoveTaskObserver(TaskQueueId queue_id,
                                               intptr_t key) {
  std::lock_guard guard(queue_mutex_);
  queue_entries_.at(queue_id)->task_observers.erase(key);
}

std::vector<zedbase::closure> MessageLoopTaskQueues::GetObserversToNotify(
    TaskQueueId queue_id) const {
  std::lock_guard guard(queue_mutex_);
  std::vector<zedbase::closure> observers;

  for (const auto& observer : queue_entries_.at(queue_id)->task_observers) {
    observers.push_back(observer.second);
  }

  return observers;
}

void MessageLoopTaskQueues::SetWakeable(TaskQueueId queue_id,
                                        zedbase::Wakeable* wakeable) {
  std::lock_guard guard(queue_mutex_);
  ZED_CHECK(!queue_entries_.at(queue_id)->wakeable)
      << "Wakeable can only be set once.";
  queue_entries_.at(queue_id)->wakeable = wakeable;
}

// Subsumed queues will never have pending tasks.
// Owning queues will consider both their and their subsumed tasks.
bool MessageLoopTaskQueues::HasPendingTasksUnlocked(
    TaskQueueId queue_id) const {
  const auto& entry = queue_entries_.at(queue_id);
  if (!entry->task_source->IsEmpty()) {
    return true;
  }
  return false;
}

zedbase::TimePoint MessageLoopTaskQueues::GetNextWakeTimeUnlocked(
    TaskQueueId queue_id) const {
  return PeekNextTaskUnlocked(queue_id).task.GetTargetTime();
}

TaskSource::TopTask MessageLoopTaskQueues::PeekNextTaskUnlocked(
    TaskQueueId owner) const {
  ZED_DCHECK(HasPendingTasksUnlocked(owner));
  const auto& entry = queue_entries_.at(owner);
  // At least one task at the top because PeekNextTaskUnlocked() is called after
  // HasPendingTasksUnlocked()
  ZED_CHECK(!entry->task_source->IsEmpty());
  return entry->task_source->Top();
}

}  // namespace zedbase
