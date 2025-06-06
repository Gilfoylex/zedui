#include "zedui/controls/control.h"

namespace zedui {
void Control::SetWidth(float width) {
  YGNodeStyleSetWidth(node_, width);
}

void Control::SetHeight(float height) {
  YGNodeStyleSetHeight(node_, height);
}

}  // namespace zedui