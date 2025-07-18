#include "zedui/widgets/widget.h"

namespace zedui {

Widget::Widget() {
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

std::shared_ptr<RootView> Widget::GetContentView() const {
  return root_view_;
}



}  // namespace zedui