#include "zedui/controls/container.h"

namespace zedui {
Container::Container() : UIContainer() {}
Container::Container(std::shared_ptr<UIContainer> parent)
    : UIContainer(parent) {}

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

} // namespace zedui