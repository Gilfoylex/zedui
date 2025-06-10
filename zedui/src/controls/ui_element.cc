#include "zedui/controls/ui_element.h"

namespace zedui {
UIElement::UIElement() : UIElement(nullptr) {}

UIElement::UIElement(std::shared_ptr<UIContainer> parent)
    : parent_(parent),
      node_(YGNodeNew()),
      last_render_rect_(Rect::MakeLTRB(0.0, 0.0, 0.0, 0.0)) {}
UIElement::~UIElement() {
  if (node_) {
    YGNodeFree(node_);
  }
}

std::shared_ptr<UIContainer> UIElement::GetParent() const {
  return parent_.lock();
}

YGNodeRef UIElement::GetNode() const {
  return node_;
}

float UIElement::GetLeft() const {
  return YGNodeLayoutGetLeft(node_);
}

float UIElement::GetTop() const {
  return YGNodeLayoutGetTop(node_);
}

float UIElement::GetWidth() const {
  return YGNodeLayoutGetWidth(node_);
}

float UIElement::GetHeight() const {
  return YGNodeLayoutGetHeight(node_);
}

Rect UIElement::GetRect() const {
  auto left = GetLeft();
  auto top = GetTop();
  auto width = GetWidth();
  auto height = GetHeight();
  return Rect::MakeLTRB(left, top, width, height);
}

Size UIElement::GetSize() const {
  return Size::MakeWH(GetWidth(), GetHeight());
}

void zedui::UIElement::MarkDirty() {
  is_dirty_ = true;
}

bool UIElement::IsDirty() const {
  if (GetRect() != last_render_rect_ || is_dirty_) {
    return true;
  }
  return false;
}

void UIElement::Draw(DrawContext& draw_context) {}

void UIElement::DrawCompleted() {
  is_dirty_ = false;
  last_render_rect_ = GetRect();
}

}  // namespace zedui