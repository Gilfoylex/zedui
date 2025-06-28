#include "zedui/render/container_layer.h"
#include "zedui/render/renderer.h"

namespace zedui {

void ContainerLayer::Add(std::shared_ptr<Layer> layer) {
  child_layers_.push_back(layer);
}

void ContainerLayer::RenderToScreen(std::shared_ptr<Renderer> renderer) {
  for (const auto& layer : child_layers_) {
    layer->RenderToScreen(renderer);
  }
}
}  // namespace zedui