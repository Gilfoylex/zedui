#include "zedui/controls/container.h"

namespace zedui {

void Container::AddChild(std::shared_ptr<Control> child) {
    childrens_.push_back(child);
    YGNodeInsertChild(node_, child->GetNode(), YGNodeGetChildCount(node_));
}

void Container::RemoveChild(std::shared_ptr<Control> child) {
    childrens_.remove(child);
    YGNodeRemoveChild(node_, child->GetNode());
}

}  // namespace zedui


