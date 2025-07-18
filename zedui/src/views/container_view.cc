#include "zedbase/logging.h"
#include "zedui/render/container_layer.h"
#include "zedui/render/draw_context.h"
#include "zedui/views/container_view.h"

namespace zedui {
ContainerView::ContainerView() : View() {}
ContainerView::~ContainerView() {}

void ContainerView::AddChild(std::shared_ptr<View> child) {
  ZED_DCHECK(child);
  child->SetParent(shared_from_this());
  childrens_.push_back(child);
  YGNodeInsertChild(node_, child->GetNode(), YGNodeGetChildCount(node_));
  Invalidate();
}

void ContainerView::RemoveChild(std::shared_ptr<View> child) {
  ZED_DCHECK(child);
  child->SetParent(nullptr);
  YGNodeRemoveChild(node_, child->GetNode());
  childrens_.remove(child);
  Invalidate();
}

void ContainerView::NotifyParentForRedraw() {
  if (auto parent = GetParent()) {
    parent->Invalidate();
  }
}

void ContainerView::Invalidate() {
  MarkDirty();
  NotifyParentForRedraw();
}

void ContainerView::MarkDirty() {
  is_dirty_ = true;
  for (const auto& child : childrens_) {
    child->MarkDirty();
  }
}

void ContainerView::Build(std::shared_ptr<ContainerLayer> layer_tree) {
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
}  // namespace zedui