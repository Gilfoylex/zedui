#include "control.h"
#include "zedui/controls/control.h"

namespace zedui {
Control::Control() : Control(nullptr) {}

Control::Control(std::shared_ptr<Control> parent)
    : parent_(parent), node_(YGNodeNew()) {}
Control::~Control() {
  if (node_) {
    YGNodeFree(node_);
  }
}

Rect Control::GetRect() const {
  auto left = YGNodeLayoutGetLeft(node_);
  auto top = YGNodeLayoutGetTop(node_);
  auto width = YGNodeLayoutGetWidth(node_);
  auto height = YGNodeLayoutGetHeight(node_);
  return Rect::MakeLTRB(left, top, width, height);
}

float Control::GetWidth() const {
  return YGNodeLayoutGetWidth(node_);
}

void Control::SetWidth(float width) {
  YGNodeStyleSetWidth(node_, width);
}

float Control::GetHeight() const {
  return YGNodeLayoutGetHeight(node_);
}

void Control::SetHeight(float height) {
  YGNodeStyleSetHeight(node_, height);
}

std::shared_ptr<Control> Control::GetParent() const {
  return parent_.lock();
}

YGNodeRef Control::GetNode() const {
  return node_;
}

void Control::Draw(const DrawContext& draw_context) {}
void Control::OnSizeChanged(const Size& old_size, const Size& new_size) {}
// todo
}  // namespace zedui