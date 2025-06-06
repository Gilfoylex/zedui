#ifndef ZEDUI_WINDOW_ZED_WINDOW_H_
#define ZEDUI_WINDOW_ZED_WINDOW_H_

#include <memory>

#include "zedui/window/win32_window.h"
#include "zedui/window/window_delegate.h"
#include "zedui/views/render_view.h"

namespace zedui {

class ZedWindow : public WindowDelegate {
 public:
  ZedWindow() = default;
  virtual ~ZedWindow() = default;

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

#endif  // ZEDUI_WINDOW_ZED_WINDOW_H_