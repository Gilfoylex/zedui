#include "zedui/widgets/native_widget.h"

namespace zedui {
NativeWidget::NativeWidget(NativeWidgetDelegate* delegate)
    : delegate_(delegate->AsWidget()->GetWeakPtr()) {
  // Initialize the native widget here if needed.
}

void* zedui::NativeWidget::GetNativeWidgetHandle() const {
  return nullptr;
}

} // namespace zedui