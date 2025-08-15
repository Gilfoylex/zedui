#include "zedui/render/scene_builder.h"
#include "zedui/render/container_layer.h"

namespace zedui {

SceneBuilder::SceneBuilder() {
  // Initialize the root layer or any other necessary components here.
  root_layer_ = zedbase::MakeRefCounted<ContainerLayer>();
  current_layer_ = root_layer_;
}

void SceneBuilder::PushContainerLayer(zedbase::RefPtr<ContainerLayer> layer) {
  if (layer) {
    current_layer_->Add(layer);
    layer_stack_.push_back(current_layer_);
    current_layer_ = layer;
  }
}

void SceneBuilder::PushLayer(zedbase::RefPtr<Layer> layer) {
  if (layer && current_layer_) {
    current_layer_->Add(layer);
  }
}

void SceneBuilder::PopContainerLayer() {
  if (!layer_stack_.empty()) {
    current_layer_ = layer_stack_.back();
    layer_stack_.pop_back();
  }
}

}  // namespace zedui