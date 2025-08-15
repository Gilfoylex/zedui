#include "zedui/widgets/native_widget.h"
#include "zedui/widgets/native_widget_delegate.h"
#include "zedui/widgets/widget.h"
#include "zedui/events/event.h"
#include "zedui/window/platform_window.h"

namespace zedui {
// static
NativeWidget* NativeWidget::CreateNativeWidget(NativeWidgetDelegate* delegate) {
  return new NativeWidget(delegate);
}

NativeWidget::NativeWidget(NativeWidgetDelegate* delegate)
    : delegate_(delegate->AsWidget()->GetWeakPtr()) {}

bool NativeWidget::CanAcceptEvent(const Event& event) {
  return false;
}

EventTarget* NativeWidget::GetParentTarget() const {
  return nullptr;
}

EventTargeter* NativeWidget::GetEventTargeter() {
  return nullptr;
}

void NativeWidget::OnCreated() {
  // 空实现，等待具体实现
}

void NativeWidget::OnDestory() {
  // 空实现，等待具体实现
}

void NativeWidget::OnSizeChanged(int width, int height) {
  // 空实现，等待具体实现
}

void NativeWidget::DispatchEvent(Event* event) {
  // 空实现，等待具体实现
}

void NativeWidget::OnWindowStateChanged(PlatformWindowState old_state,
                                        PlatformWindowState new_state) {
  // 空实现，等待具体实现
}

} // namespace zedui
