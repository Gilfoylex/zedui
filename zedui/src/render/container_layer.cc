#include "zedui/render/container_layer.h"

namespace zedui {

void ContainerLayer::Add(std::shared_ptr<Layer> layer) {
  child_layers_.push_back(layer);
}

void ContainerLayer::RenderToScreen(const std::shared_ptr<Renderer>& renderer) {
  for (const auto& layer : child_layers_) {
    layer->RenderToScreen(renderer);
  }
}
}  // namespace zedui