#include "zedui/widgets/widget.h"

namespace zedui {

Widget::Widget() {
  native_widget_ = std::make_unique<NativeWidgetWin>(this);
  root_view_ = std::make_unique<RootView>(this);
}

zedbase::WeakPtr<Widget> Widget::GetWeakPtr() {
  return weak_ptr_factory_.GetWeakPtr();
}

View* Widget::GetRootView() {
  return root_view_.get();
}

const View* Widget::GetRootView() const {
  return root_view_.get();
}

Widget* Widget::AsWidget() {
  return this;
}
const Widget* Widget::AsWidget() const {
  return this;
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

EventSink* Widget::GetEventSink() {
  return root_view_.get();
}



}  // namespace zedui