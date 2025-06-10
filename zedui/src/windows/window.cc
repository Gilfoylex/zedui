#include "zedui/windows/window.h"

namespace zedui {
Window::Window() {}
Window::~Window() {}
void Window::OnCreated() {}
void Window::OnDestroyed() {}
void Window::OnSizeChanged(int width, int height) {
  PerformLayout(static_cast<float>(width), static_cast<float>(height),
                YGDirectionLTR);
}

void Window::PerformLayout(float width, float height, YGDirection direction) {
  // todo set width & height
  YGNodeCalculateLayout(node_, width, height, direction);
}
}  // namespace zedui