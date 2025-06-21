#include "zedui/controls/container.h"
#include "yoga/Yoga.h"

namespace zedui {
Container::Container() : UIContainer() {}

void Container::SetWidth(float width){
    YGNodeStyleSetWidth(node_, width);
    Invalidate();
}

void Container::SetHeight(float height){
  YGNodeStyleSetHeight(node_, height);
  Invalidate();
}

void Container::SetSize(const Size& size){
  YGNodeStyleSetWidth(node_, size.width);
  YGNodeStyleSetHeight(node_, size.height);
  Invalidate();
}

void Container::SetFlexDirection() {
  YGNodeStyleSetFlexDirection(node_, YGFlexDirectionRow);
  YGNodeStyleSetFlexWrap(node_, YGWrapWrap);
  Invalidate();
}
} // namespace zedui