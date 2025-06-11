#ifndef ZEDUI_WINDOWS_WINDOW_H_
#define ZEDUI_WINDOWS_WINDOW_H_

#include <memory>

#include "yoga/Yoga.h"

#include "zedbase/macros.h"

#include "zedui/controls/container.h"
#include "zedui/windows/win32_window.h"
#include "zedui/windows/window_delegate.h"

namespace zedui {

class Window : public WindowDelegate, Container {
 public:
  Window();
  virtual ~Window();

  // WindowDelegate overrides
  void OnCreated() override;

  void OnDestroyed() override;

  void OnSizeChanged(int width, int height) override;


  // Container overrides
  void NotifyParentForRedraw() override;
  void Draw(DrawContext& draw_context) override;
  void DrawCompleted() override;
 private:
  void PerformLayout(float width, float height, YGDirection direction);
  void DoFrame();

 private:
  Win32Window win32_window_;
  bool in_redraw_;
  ZED_DISALLOW_COPY_ASSIGN_AND_MOVE(Window);
};

}  // namespace zedui

#endif  // ZEDUI_WINDOWS_WINDOW_H_