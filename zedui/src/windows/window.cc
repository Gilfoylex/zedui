#include "zedui/windows/window.h"

namespace zedui {
Window::Window() {}
void Window::OnCreated() {}
void Window::OnDestroyed() {}
void Window::OnSizeChanged(int width, int height) {
  if (render_view_ == nullptr) {
    return;
  }

  render_view_->PerformLayout(static_cast<float>(width),
                              static_cast<float>(height), YGDirectionLTR);
}
}  // namespace zedui