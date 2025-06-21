#include "zedui/controls/control.h"

namespace zedui {

Control::Control() : UIElement() {}
Control::~Control() {}

void Control::SetWidth(float width) {
  YGNodeStyleSetWidth(node_, width);
  Invalidate();
}

void Control::SetHeight(float height) {
  YGNodeStyleSetHeight(node_, height);
  Invalidate();
}

void Control::SetSize(Size size) {
  YGNodeStyleSetWidth(node_, size.width);
  YGNodeStyleSetHeight(node_, size.height);
  YGNodeStyleSetMargin(node_, YGEdgeLeft, 10);
  YGNodeStyleSetMargin(node_, YGEdgeTop, 10);
  YGNodeStyleSetMargin(node_, YGEdgeRight, 10);
  YGNodeStyleSetMargin(node_, YGEdgeBottom, 10);
  Invalidate();
}

void zedui::Control::SetFlexGrow(float flex_grow) {
  YGNodeStyleSetFlexGrow(node_, flex_grow);
}

}  // namespace zedui