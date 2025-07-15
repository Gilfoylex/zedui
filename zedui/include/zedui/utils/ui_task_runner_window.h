#pragma once

#include <windows.h>

#include <memory>
#include <string>
#include <vector>

#include "zedbase/macros.h"
#include "zedbase/time/time_delta.h"

namespace zedui {

class UITaskRunnerWindow {
 public:
  class Delegate {
   public:
    virtual zedbase::TimeDelta ProcessTasks() = 0;
  };

  static std::shared_ptr<UITaskRunnerWindow> GetSharedInstance();

  void WakeUp();

  void AddDelegate(Delegate* delegate);
  void RemoveDelegate(Delegate* delegate);

  ~UITaskRunnerWindow();

 private:
  UITaskRunnerWindow();

  void ProcessTasks();
  void SetTimer(zedbase::TimeDelta when);

  WNDCLASS RegisterWindowClass();

  LRESULT
  HandleMessage(UINT const message,
                WPARAM const wparam,
                LPARAM const lparam) noexcept;

  static LRESULT CALLBACK WndProc(HWND const window,
                                  UINT const message,
                                  WPARAM const wparam,
                                  LPARAM const lparam) noexcept;

  HWND window_handle_;
  std::wstring window_class_name_;
  std::vector<Delegate*> delegates_;

  ZED_DISALLOW_COPY_AND_ASSIGN(UITaskRunnerWindow);
};

}  // namespace zedui