#include "zedui/controls/control.h"

namespace zedui {

Control::Control() : UIElement() {}
Control::Control(std::shared_ptr<UIContainer> parent)
    : UIElement(parent) {
}

void Control::SetWidth(float width) {
  YGNodeStyleSetWidth(node_, width);
}

void Control::SetHeight(float height) {
  YGNodeStyleSetHeight(node_, height);
}

}  // namespace zedui