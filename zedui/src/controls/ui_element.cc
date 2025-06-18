#include "zedui/controls/ui_element.h"
#include "zedui/controls/ui_container.h"

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

std::shared_ptr<zedui::PictureLayer> UIElement::GetPictureLayer() {
  // use the parent container's picture layer if available
  return GetParent()->GetPictureLayer();
}

void UIElement::Invalidate() {
  MarkDirty();
  auto parent = GetParent();
  if (parent){
    parent->MarkDirty();
    parent->NotifyParentForRedraw();
  }
}

void zedui::UIElement::MarkDirty() {
  is_dirty_ = true;
}

bool UIElement::IsDirty() const {
  if (is_dirty_ || GetRect() != last_render_rect_) {
    return true;
  }
  return false;
}

void UIElement::Build(std::shared_ptr<ContainerLayer> layer_tree) {
  // Need UIContainer to build the layer tree
  if (IsDirty()) {
    auto draw_context = DrawContext(GetLeft(), GetTop(), GetPictureLayer());
    Draw(draw_context);
  }
}

void UIElement::Draw(DrawContext& draw_context) {}

void UIElement::DrawCompleted() {
  is_dirty_ = false;
  last_render_rect_ = GetRect();
}

}  // namespace zedui