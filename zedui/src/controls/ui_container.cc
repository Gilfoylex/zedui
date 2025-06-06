#include "zedui/controls/ui_container.h"

namespace zedui {

void UIContainer::Add(std::shared_ptr<UIElement> child) {
  childrens_.push_back(child);
  YGNodeInsertChild(node_, child->GetNode(), YGNodeGetChildCount(node_));
}

void UIContainer::Remove(std::shared_ptr<UIElement> child) {
  childrens_.remove(child);
  YGNodeRemoveChild(node_, child->GetNode());
}

void UIContainer::Draw(const DrawContext& draw_context) {
  for (const auto& child : childrens_) {
    if (child->IsDirty()) {
      child->Draw(draw_context);
      child->EndDraw();
    }
  }
}

}  // namespace zedui
