#include "zedui/controls/ui_container.h"

namespace zedui {

UIContainer::UIContainer() : UIElement(), picture_layer_(nullptr) {}

void UIContainer::Add(std::shared_ptr<UIElement> child) {
  childrens_.push_back(child);
  YGNodeInsertChild(node_, child->GetNode(), YGNodeGetChildCount(node_));
  child->SetParent(shared_from_this());
  Invalidate();
}

void UIContainer::Remove(std::shared_ptr<UIElement> child) {
  child->SetParent(nullptr);
  YGNodeRemoveChild(node_, child->GetNode());
  childrens_.remove(child);
  Invalidate();
}

void UIContainer::Invalidate() {
  MarkDirty();
  NotifyParentForRedraw();
}

void UIContainer::MarkDirty() {
  is_dirty_ = true;
  for (auto const& child : childrens_) {
    child->MarkDirty();
  }
}

void UIContainer::Build(std::shared_ptr<ContainerLayer> layer_tree) {
  auto container_layer = std::make_shared<zedui::ContainerLayer>();
  layer_tree->Add(container_layer);
  auto picture_layer = GetPictureLayer();
  if (picture_layer) {
    container_layer->Add(picture_layer);
  }
  if (IsDirty()) {
    auto draw_context = DrawContext(GetLeft(), GetTop(), picture_layer);
    Draw(draw_context);
  }
  for (const auto& child : childrens_) {
    child->Build(container_layer);
  }
}

void UIContainer::Draw(DrawContext& draw_context) {
  // do nothing
}

std::shared_ptr<zedui::PictureLayer> UIContainer::GetPictureLayer() {
  // create new pictureLayer if it is dirty or not created
  if (IsDirty() || !picture_layer_) {
    picture_layer_ = std::make_shared<zedui::PictureLayer>(
        GetLeft(), GetTop(), GetWidth(), GetHeight());
  }

  // else, return the existing PictureLayer(cached)
  return picture_layer_;
}

void UIContainer::NotifyParentForRedraw() {
  auto parent = GetParent();
  if (parent) {
    parent->NotifyParentForRedraw();
  }
}

}  // namespace zedui
