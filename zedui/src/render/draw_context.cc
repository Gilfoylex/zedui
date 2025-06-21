#include "zedui/render/draw_context.h"

namespace zedui {

DrawContext::DrawContext(float left,
                         float top,
                         std::shared_ptr<PictureLayer> picture_layer)
    : picture_layer_(picture_layer) {
  left_offset_ = left - picture_layer->GetLeft();
  top_offset_ = top - picture_layer->GetTop();
}

void zedui::DrawContext::DrawCircle(float x, float y, float radius) {
  auto draw_command = std::make_shared<DrawCircleCommand>(
      x + left_offset_, y + top_offset_, radius);
  picture_layer_->PushDrawCommand(draw_command);
}

void zedui::DrawContext::DrawRectangle(float x,
                                       float y,
                                       float width,
                                       float height) {
  // auto draw_command = std::make_shared<DrawRectCommand>(
  //     x + left_offset_, y + top_offset_, width, height);

      auto draw_command = std::make_shared<DrawRectCommand>(
      x, y, width, height);
  picture_layer_->PushDrawCommand(draw_command);
}

}  // namespace zedui
