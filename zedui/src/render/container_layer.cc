#include "zedui/render/container_layer.h"
#include "zedui/render/renderer.h"

namespace zedui {

void ContainerLayer::Add(zedbase::RefPtr<Layer> layer) {
  child_layers_.push_back(layer);
}

void ContainerLayer::RenderToScreen(zedbase::WeakPtr<Renderer> renderer) {
  for (const auto& layer : child_layers_) {
    layer->RenderToScreen(renderer);
  }
}
}  // namespace zedui