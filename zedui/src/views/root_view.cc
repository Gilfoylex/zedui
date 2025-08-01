#include "zedui/render/container_layer.h"
#include "zedui/views/root_view.h"
#include "zedui/render/draw_context.h"

namespace zedui {

RootView::RootView(RootViewDelegate* delegate)
: delegate_(delegate), ContainerView() {}
RootView::~RootView() {}

void RootView::NotifyParentForRedraw() {
  if (delegate_) {
    delegate_->TriggerRedraw();
  }
}

void RootView::OnEventFromSource(Event* event) {
   // todo
}

std::shared_ptr<ContainerLayer> RootView::BuildLayerTree() {
  YGNodeCalculateLayout(node_, YGUndefined, YGUndefined, YGDirectionLTR);
  auto container_layer = std::make_shared<zedui::ContainerLayer>();
  auto picture_layer = GetPictureLayer();
  if (picture_layer) {
    container_layer->Add(picture_layer);
  }
  if (IsDirty()) {
    auto draw_context = DrawContext(GetLeft(), GetTop(), picture_layer);
    Draw(draw_context);
    DrawCompleted();
  }
  for (const auto& child : childrens_) {
    child->Build(container_layer);
  }

  return container_layer;
}

void RootView::Build(std::shared_ptr<ContainerLayer> layer_tree) {
    // RootView does not need to build its own layer tree,
}

}  // namespace zedui