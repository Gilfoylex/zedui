#include "zedui_window.h"

#include <thread>

namespace zedui {

ZedUiWindow::~ZedUiWindow() {}

bool ZedUiWindow::OnCreate() {
  Show();
  graphics_ = std::make_unique<Graphics>();
  if (!graphics_->Initialize(GetHandle())) {
    return false;
  }

  /*task_runner_ = std::make_unique<zedui::TaskRunner>();
  auto that = this;
  task_thread_ = std::thread([that] {
    int i = 0;
    while (i++ < 100) {
      std::this_thread::sleep_for(std::chrono::microseconds(16));
      that->task_runner_->PostTask([that] { 
              that->graphics_->BeginDraw();
        that->graphics_->ClearScreen(0.0f, 0.0f, 0.0f);
              that->graphics_->DrawCircle(100.0f, 100.0f, 50.0f, 1.0f, 0.0f,
                                          0.0f, 1.0f);
        that->graphics_->EndDraw();
          });
    }
  });*/
  auto x = 1;       
  auto y = 2;    
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

}  // namespace zedui
