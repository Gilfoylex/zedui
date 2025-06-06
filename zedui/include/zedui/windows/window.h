#ifndef ZEDUI_WINDOWS_WINDOW_H_
#define ZEDUI_WINDOWS_WINDOW_H_

#include <memory>

#include "zedui/windows/win32_window.h"
#include "zedui/windows/window_delegate.h"
#include "zedui/views/render_view.h"

namespace zedui {

class Window : public WindowDelegate {
 public:
  Window();
  virtual ~Window();

  // WindowDelegate overrides
  void OnCreated() override;

  void OnDestroyed() override;

  void OnSizeChanged(int width, int height) override;

  // Additional methods specific to ZedWindow can be added here

 private:
  Win32Window win32_window_;
  std::shared_ptr<RenderView> render_view_;
};

}  // namespace zedui

#endif  // ZEDUI_WINDOWS_WINDOW_H_