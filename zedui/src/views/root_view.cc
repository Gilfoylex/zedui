#include "zedui/render/container_layer.h"
#include "zedui/views/root_view.h"
#include "zedui/render/draw_context.h"
#include "zedui/render/scene_builder.h"

namespace zedui {

RootView::RootView()
: View() {}
RootView::~RootView() {}

void RootView::OnEventFromSource(Event* event) {
   // todo
}

void RootView::BuildScene(SceneBuilder* scene_builder)
{
  YGNodeCalculateLayout(node_, YGUndefined, YGUndefined, YGDirectionLTR);
  if (IsDirty()) {
    ReCreatePictureLayer();
    scene_builder->PushLayer(GetPictureLayer());
    DrawContext draw_context(GetPictureLayer());
    OnDraw(draw_context);
    DrawCompleted();
  }

  for (auto child : children_) {
    child->BuildScene(scene_builder);
  }
}

}  // namespace zedui