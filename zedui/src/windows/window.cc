#include "zedui/app.h"
#include "zedui/windows/window.h"


namespace zedui {
Window::Window() : in_redraw_(false) {}
Window::~Window() {}
void Window::OnCreated() {
  // create render target
}
void Window::OnDestroyed() {}
void Window::OnSizeChanged(int width, int height) {
  PerformLayout(static_cast<float>(width), static_cast<float>(height),
                YGDirectionLTR);
  MarkDirty();
  NotifyParentForRedraw();
}

void Window::PerformLayout(float width, float height, YGDirection direction) {
  SetWidth(width);
  SetHeight(height);
  YGNodeCalculateLayout(node_, width, height, direction);
}

void Window::NotifyParentForRedraw() {
  if (in_redraw_) {
    return;
  }
  in_redraw_ = true;
  App::Current->PostVsyncTask([this]() { DoFrame(); });
}

void Window::DrawCompleted() {
  Container::DrawCompleted();
}

void Window::DoFrame() {
  in_redraw_ = false;
}

}  // namespace zedui