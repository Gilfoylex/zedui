#include "zedui/controls/ui_element.h"

namespace zedui {
UIElement::UIElement() : UIElement(nullptr) {}

UIElement::UIElement(std::shared_ptr<UIElement> parent)
    : parent_(parent), node_(YGNodeNew()) {}
UIElement::~UIElement() {
  if (node_) {
    YGNodeFree(node_);
  }
}

Rect UIElement::GetRect() const {
  auto left = YGNodeLayoutGetLeft(node_);
  auto top = YGNodeLayoutGetTop(node_);
  auto width = YGNodeLayoutGetWidth(node_);
  auto height = YGNodeLayoutGetHeight(node_);
  return Rect::MakeLTRB(left, top, width, height);
}

float UIElement::GetWidth() const {
  return YGNodeLayoutGetWidth(node_);
}

void UIElement::SetWidth(float width) {
  YGNodeStyleSetWidth(node_, width);
}

float UIElement::GetHeight() const {
  return YGNodeLayoutGetHeight(node_);
}

void UIElement::SetHeight(float height) {
  YGNodeStyleSetHeight(node_, height);
}

std::shared_ptr<UIElement> UIElement::GetParent() const {
  return parent_.lock();
}

YGNodeRef UIElement::GetNode() const {
  return node_;
}

void zedui::UIElement::MarkDirty() {
  is_dirty_ = true;
}

bool UIElement::IsDirty() const {
  return is_dirty_;
}

std::shared_ptr<zedui::PictureLayer> UIElement::GetPictureLayer() {
  return picture_layer_;
}

void UIElement::Draw(const DrawContext& draw_context) {}

void UIElement::EndDraw() {
  is_dirty_ = false;
}

}  // namespace zedui