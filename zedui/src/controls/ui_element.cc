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

bool UIElement::NeedRedraw() const {
  return need_redraw_;
}

std::shared_ptr<zedui::Layer> UIElement::GetLayer() {
  return layer_;
}

void UIElement::Draw(const DrawContext& draw_context) {}

void UIElement::DrawFinished() {
  need_redraw_ = false;
}

void UIElement::OnSizeChanged(const Size& old_size, const Size& new_size) {}
}  // namespace zedui