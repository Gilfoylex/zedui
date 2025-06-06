#include "zedui/render/draw_context.h"

namespace zedui {

DrawContext::DrawContext() {}

void zedui::DrawContext::DrawCircle(float x, float y, float radius) {}
void zedui::DrawContext::DrawRectangle(float x,
                                       float y,
                                       float width,
                                       float height) {}

std::shared_ptr<ContainerLayer> zedui::DrawContext::GetLayerContainer() const {
  return layer_container_;
}

void DrawContext::AddLayerContainer(
    std::shared_ptr<ContainerLayer> layer_container) {
  if (layer_container_ == nullptr) {
    layer_container_ = layer_container;
  }
  else {
    layer_container_->Add(layer_container);
  }
}

void DrawContext::PushPictureLayer(
    std::shared_ptr<PictureLayer> picture_layer) {
  picture_layers_.push(picture_layer);
}

void zedui::DrawContext::PopPictureLayer() {
  if (!picture_layers_.empty()) {
    picture_layers_.pop();
  }
}

}  // namespace zedui
