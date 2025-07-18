#include "zedbase/logging.h"
#include "zedui/render/container_layer.h"
#include "zedui/render/draw_context.h"
#include "zedui/render/picture_layer.h"
#include "zedui/views/view.h"

namespace zedui {
View::View() : node_(YGNodeNew()), is_dirty_(true) {}
View::~View() {
  if (node_) {
    YGNodeFree(node_);
  }
}

std::shared_ptr<ContainerView> View::GetParent() const {
  return parent_.lock();
}

YGNodeRef View::GetNode() const {
  return node_;
}

float View::GetLeft() const {
  return YGNodeLayoutGetLeft(node_);
}

float View::GetTop() const {
  return YGNodeLayoutGetTop(node_);
}

float View::GetRight() const {
  return YGNodeLayoutGetRight(node_);
}

float View::GetBottom() const {
  return YGNodeLayoutGetBottom(node_);
}

float View::GetWidth() const {
  return YGNodeLayoutGetWidth(node_);
}

float View::GetHeight() const {
  return YGNodeLayoutGetHeight(node_);
}

void View::SetWidth(float width) {
  YGNodeStyleSetWidth(node_, width);
  Invalidate();
}

void View::SetHeight(float height) {
  YGNodeStyleSetHeight(node_, height);
  Invalidate();
}

Rect View::GetLocalBounds() const {
  return Rect::MakeXYWH(GetLeft(), GetTop(), GetWidth(), GetHeight());
}

std::shared_ptr<zedui::PictureLayer> View::GetPictureLayer() {
  ZED_DCHECK(GetParent());
  return GetParent()->GetPictureLayer();
}

void View::Invalidate() {
  MarkDirty();
  if (auto parent = GetParent()) {
    parent->MarkDirty();
    parent->NotifyParentForRedraw();
  }
}

void View::SetParent(std::shared_ptr<ContainerView> parent) {
  parent_ = parent;
}

bool View::IsDirty() const {
  return is_dirty_;
}

void View::MarkDirty() {
  is_dirty_ = true;
}

void View::Build(std::shared_ptr<ContainerLayer> layer_tree) {
  // Need ContainerView to build the layer tree
  if (IsDirty()) {
    auto draw_context = DrawContext(GetLeft(), GetTop(), GetPictureLayer());
    Draw(draw_context);
    DrawCompleted();
  }
}

void View::Draw(DrawContext& draw_context) {
  // Default implementation does nothing
  ZED_LOG(kLogWarning) << "Draw method not implemented for "
                       << typeid(*this).name();
}

void View::DrawCompleted() {
  is_dirty_ = false;
}

}  // namespace zedui