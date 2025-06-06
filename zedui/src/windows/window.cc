#include "zedui/windows/window.h"

namespace zedui {
Window::Window() {
  render_view_ = std::make_shared<zedui::RenderView>();
}
void Window::OnCreated() {}
void Window::OnDestroyed() {}
void Window::OnSizeChanged(int width, int height) {
  render_view_->PerformLayout(static_cast<float>(width),
                              static_cast<float>(height), YGDirectionLTR);
}
}  // namespace zedui