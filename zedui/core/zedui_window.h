#ifndef ZEDUI_WINDOW_H
#define ZEDUI_WINDOW_H

#include <memory>

#include "win32_window.h"

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
};
}  // namespace zedui

#endif  // ZEDUI_WINDOW_H