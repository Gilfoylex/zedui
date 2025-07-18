#pragma once
#include <memory>
#include "zedbase/macros.h"
#include "zedbase/memory/weak_ptr.h"
#include "zedui/render/renderer.h"
#include "zedui/views/root_view.h"
#include "zedui/windows/win32_window.h"
#include "zedui/widgets/native_widget_delegate.h"

namespace zedui {
class Widget : public RootViewDelegate, public NativeWidgetDelegate {
 public:
  Widget();
  zedbase::WeakPtr<Widget> GetWeakPtr();
  std::shared_ptr<RootView> GetContentView() const;

  Widget* AsWidget() override;
  const Widget* AsWidget() const override;

 private:
  std::unique_ptr<Win32Window> win32_window_;
  std::shared_ptr<RootView> root_view_;
  std::shared_ptr<Renderer> renderer_;
  zedbase::WeakPtrFactory<Widget> weak_ptr_factory_{this};
  ZED_DISALLOW_COPY_ASSIGN_AND_MOVE(Widget);
};
}  // namespace zedui