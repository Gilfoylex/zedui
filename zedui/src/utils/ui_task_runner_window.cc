#include "zedbase/logging.h"
#include "zedui/utils/ui_task_runner_window.h"

#include <algorithm>

namespace zedui {

UITaskRunnerWindow::UITaskRunnerWindow() {
  WNDCLASS window_class = RegisterWindowClass();
  window_handle_ =
      CreateWindowEx(0, window_class.lpszClassName, L"", 0, 0, 0, 0, 0,
                     HWND_MESSAGE, nullptr, window_class.hInstance, nullptr);

  if (window_handle_) {
    SetWindowLongPtr(window_handle_, GWLP_USERDATA,
                     reinterpret_cast<LONG_PTR>(this));
  } else {
    auto error = GetLastError();
    LPWSTR message = nullptr;
    size_t size = FormatMessageW(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        reinterpret_cast<LPWSTR>(&message), 0, NULL);
    OutputDebugString(message);
    LocalFree(message);
  }
}

UITaskRunnerWindow::~UITaskRunnerWindow() {
  if (window_handle_) {
    DestroyWindow(window_handle_);
    window_handle_ = nullptr;
  }
  UnregisterClass(window_class_name_.c_str(), nullptr);
}

std::shared_ptr<UITaskRunnerWindow> UITaskRunnerWindow::GetSharedInstance() {
  static std::weak_ptr<UITaskRunnerWindow> instance;
  auto res = instance.lock();
  if (!res) {
    // can't use make_shared with private contructor
    res.reset(new UITaskRunnerWindow());
    instance = res;
  }
  return res;
}

void UITaskRunnerWindow::WakeUp() {
  if (!PostMessage(window_handle_, WM_NULL, 0, 0)) {
    ZED_LOG(kLogError) << "Failed to post message to main thread.";
  }
}

void UITaskRunnerWindow::AddDelegate(Delegate* delegate) {
  delegates_.push_back(delegate);
  SetTimer(zedbase::TimeDelta::Zero());
}

void UITaskRunnerWindow::RemoveDelegate(Delegate* delegate) {
  auto i = std::find(delegates_.begin(), delegates_.end(), delegate);
  if (i != delegates_.end()) {
    delegates_.erase(i);
  }
}

void UITaskRunnerWindow::ProcessTasks() {
  auto next = zedbase::TimeDelta::Max();
  auto delegates_copy(delegates_);
  for (auto delegate : delegates_copy) {
    // if not removed in the meanwhile
    if (std::find(delegates_.begin(), delegates_.end(), delegate) !=
        delegates_.end()) {
      next = std::min(next, delegate->ProcessTasks());
    }
  }
  SetTimer(next);
}

void UITaskRunnerWindow::SetTimer(zedbase::TimeDelta when) {
  if (when == zedbase::TimeDelta::Max()) {
    KillTimer(window_handle_, 0);
  } else {
    auto millis = when.ToMilliseconds();
    ::SetTimer(window_handle_, 0, static_cast<UINT>(millis + 1), nullptr);
  }
}

WNDCLASS UITaskRunnerWindow::RegisterWindowClass() {
  window_class_name_ = L"ZedUiTaskRunnerWindow";

  WNDCLASS window_class{};
  window_class.hCursor = nullptr;
  window_class.lpszClassName = window_class_name_.c_str();
  window_class.style = 0;
  window_class.cbClsExtra = 0;
  window_class.cbWndExtra = 0;
  window_class.hInstance = GetModuleHandle(nullptr);
  window_class.hIcon = nullptr;
  window_class.hbrBackground = 0;
  window_class.lpszMenuName = nullptr;
  window_class.lpfnWndProc = WndProc;
  RegisterClass(&window_class);
  return window_class;
}

LRESULT
UITaskRunnerWindow::HandleMessage(UINT const message,
                                  WPARAM const wparam,
                                  LPARAM const lparam) noexcept {
  switch (message) {
    case WM_TIMER:
    case WM_NULL:
      ProcessTasks();
      return 0;
  }
  return DefWindowProcW(window_handle_, message, wparam, lparam);
}

LRESULT UITaskRunnerWindow::WndProc(HWND const window,
                                    UINT const message,
                                    WPARAM const wparam,
                                    LPARAM const lparam) noexcept {
  if (auto* that = reinterpret_cast<UITaskRunnerWindow*>(
          GetWindowLongPtr(window, GWLP_USERDATA))) {
    return that->HandleMessage(message, wparam, lparam);
  } else {
    return DefWindowProc(window, message, wparam, lparam);
  }
}

}  // namespace zedui