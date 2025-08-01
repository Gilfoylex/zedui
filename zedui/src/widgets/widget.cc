#include "zedui/widgets/widget.h"

namespace zedui {

Widget::Widget() {
  native_widget_ = std::make_unique<NativeWidgetWin>(this);
  root_view_ = std::make_shared<RootView>(this);
}

zedbase::WeakPtr<Widget> Widget::GetWeakPtr() {
  return weak_ptr_factory_.GetWeakPtr();
}

Widget* Widget::AsWidget() {
  return this;
}
const Widget* Widget::AsWidget() const {
  return this;
}

void Widget::TriggerRedraw() {
  // todo
}

void Widget::OnNativeWidgetCreated() {
  // todo
}

void Widget::OnNativeWidgetDestroyed() {
  // todo
}

void Widget::OnNativeWidgetSizeChanged(const Size& new_size) {
  // todo
}

std::shared_ptr<RootView> Widget::GetContentView() const {
  return root_view_;
}



}  // namespace zedui