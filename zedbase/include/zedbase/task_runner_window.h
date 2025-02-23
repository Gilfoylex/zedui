#ifndef TASK_RUNNER_WINDOW_H_
#define TASK_RUNNER_WINDOW_H_

#include <windows.h>

#include <chrono>
#include <memory>
#include <string>
#include <vector>

#include "zebase/macros.h"

namespace zedbase {

class TaskRunnerWindow {
 public:
  class Delegate {
   public:
    virtual std::chrono::nanoseconds ProcessTasks() = 0;
  };

  static std::shared_ptr<TaskRunnerWindow> GetSharedInstance();

  void WakeUp();

  void AddDelegate(Delegate* delegate);
  void RemoveDelegate(Delegate* delegate);

  ~TaskRunnerWindow();

 private:
  TaskRunnerWindow();

  void ProcessTasks();
  void SetTimer(std::chrono::nanoseconds when);

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

  ZED_DISALLOW_COPY_AND_ASSIGN(TaskRunnerWindow);
};

}  // namespace zedbase

#endif  // TASK_RUNNER_WINDOW_H_