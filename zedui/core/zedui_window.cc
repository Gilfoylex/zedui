#include "zedui_window.h"

namespace zedui {
  
ZedUiWindow::~ZedUiWindow() {}

bool ZedUiWindow::OnCreate() {
  Show();
  return true;
}

void ZedUiWindow::OnDestroy() {
  Win32Window::OnDestroy();
}

LRESULT ZedUiWindow::MessageHandler(HWND window,
                                    UINT const message,
                                    WPARAM const wparam,
                                    LPARAM const lparam) noexcept {
  return Win32Window::MessageHandler(window, message, wparam, lparam);
}

} // namespace zedui
