#include "zedui/controls/ui_container.h"

namespace zedui {

void UIContainer::Add(std::shared_ptr<UIElement> child) {
  childrens_.push_back(child);
  YGNodeInsertChild(node_, child->GetNode(), YGNodeGetChildCount(node_));
}

void UIContainer::Remove(std::shared_ptr<UIElement> child) {
  YGNodeRemoveChild(node_, child->GetNode());
  childrens_.remove(child);
}

void UIContainer::Draw(DrawContext& draw_context) {
  auto cur_picture_layer = GetPictureLayer();
  draw_context.PushPictureLayer(cur_picture_layer);
  for (const auto& child : childrens_) {
    // container was dirty， we need drawing all children
    child->Draw(draw_context);
    child->DrawCompleted();
  }
  draw_context.PopPictureLayer();
}

std::shared_ptr<zedui::PictureLayer> UIContainer::GetPictureLayer() {
  // create new pictureLayer if it is dirty or not created
  if (IsDirty() || !picture_layer_) {
    picture_layer_ = std::make_shared<zedui::PictureLayer>();
  }

  // else, return the existing PictureLayer(cached)
  return picture_layer_;
}

}  // namespace zedui
