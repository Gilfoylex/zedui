#ifndef ZEDUI_WINDOW_H
#define ZEDUI_WINDOW_H

#include <memory>

#include "zedui/base/task_runner.h"
#include "win32_window.h"
#include "graphics.h"

namespace zedui {
class ZedUiWindow : public Win32Window {
 public:
  virtual ~ZedUiWindow();

 protected:
  bool OnCreate() override;
  void OnDestroy() override;
  LRESULT MessageHandler(HWND window,
                         UINT const message,
                         WPARAM const wparam,
                         LPARAM const lparam) noexcept override;

    private:
    std::unique_ptr<Graphics> graphics_;
    std::unique_ptr<TaskRunner> task_runner_;
    std::thread task_thread_;
};
}  // namespace zedui

#endif  // ZEDUI_WINDOW_H