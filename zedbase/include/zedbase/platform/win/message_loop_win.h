// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ZEDBASE_PLATFORM_WIN_MESSAGE_LOOP_WIN_H_
#define ZEDBASE_PLATFORM_WIN_MESSAGE_LOOP_WIN_H_

#include <windows.h>

#include <atomic>

#include "zedbase/macros.h"
#include "zedbase/message_loop_impl.h"
#include "zedbase/unique_object.h"

namespace zedbase {

class MessageLoopWin : public MessageLoopImpl {
 private:
  struct UniqueHandleTraits {
    static HANDLE InvalidValue() { return NULL; }
    static bool IsValid(HANDLE value) { return value != NULL; }
    static void Free(HANDLE value) { CloseHandle(value); }
  };

  bool running_;
  zedbase::UniqueObject<HANDLE, UniqueHandleTraits> timer_;
  uint32_t timer_resolution_;

  MessageLoopWin();

  ~MessageLoopWin() override;

  void Run() override;

  void Terminate() override;

  void WakeUp(zedbase::TimePoint time_point) override;

  ZED_FRIEND_MAKE_REF_COUNTED(MessageLoopWin);
  ZED_FRIEND_REF_COUNTED_THREAD_SAFE(MessageLoopWin);
  ZED_DISALLOW_COPY_AND_ASSIGN(MessageLoopWin);
};

}  // namespace zedbase

#endif  // ZEDBASE_PLATFORM_WIN_MESSAGE_LOOP_WIN_H_
