#pragma once
#include <memory>
#include "zedbase/memory/weak_ptr.h"
#include "zedui/widgets/native_widget_delegate.h"
#include "zedui/widgets/native_widget_private.h"
#include "zedui/windows/win32_window.h"
#include "zedui/windows/window_delegate.h"

namespace zedui {
class NativeWidgetWin32 : public NativeWidgetPrivate, public WindowDelegate {
 public:
  explicit NativeWidgetWin32(NativeWidgetDelegate* delegate);
  virtual ~NativeWidgetWin32() override;

  // WindowDelegate overrides
  void OnCreated() override;
  void OnDestroyed() override;
  void OnSizeChanged(int width, int height) override;

  // NativeWidgetPrivate overrides
  // void DestroyNativeWidget() override;
  void* GetNativeWidgetHandle() const override;
  void Show(WindowShowState show_state) override;

 private:
  std::unique_ptr<Win32Window> win32_window_;
  zedbase::WeakPtr<NativeWidgetDelegate> delegate_;
};

}  // namespace zedui