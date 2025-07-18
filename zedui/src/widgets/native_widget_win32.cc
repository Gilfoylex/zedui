#include "zedbase/logging.h"
#include "zedui/geometry/size.h"
#include "zedui/widgets/native_widget_win32.h"
#include "zedui/widgets/widget.h"

namespace zedui {
NativeWidgetWin32::NativeWidgetWin32(NativeWidgetDelegate* delegate)
    : delegate_(delegate->AsWidget()->GetWeakPtr()) {
  win32_window_ = std::make_unique<Win32Window>();
  win32_window_->SetWindowDelegate(this);
  win32_window_->SetQuitOnClose(true);
  Win32Window::Point origin(10, 10);
  Win32Window::Size size(600, 400);
  auto success = win32_window_->Create(L"ZedUI Native Widget", origin, size);
  ZED_CHECK(success) << "Failed to create Win32 window.";
}

NativeWidgetWin32::~NativeWidgetWin32() {}

void* NativeWidgetWin32::GetNativeWidgetHandle() const {
  return win32_window_->GetHandle();
}

void NativeWidgetWin32::OnCreated() {
  if (delegate_) {
    delegate_->OnNativeWidgetCreated();
  }
}

void NativeWidgetWin32::OnDestroyed() {
  if (delegate_) {
    delegate_->OnNativeWidgetDestroyed();
  }
}

void NativeWidgetWin32::OnSizeChanged(int width, int height) {
  if (delegate_) {
    delegate_->OnNativeWidgetSizeChanged(Size::MakeWH(width, height));
  }
}

void NativeWidgetWin32::Show(WindowShowState show_state) {
  win32_window_->Show();
}

}  // namespace zedui