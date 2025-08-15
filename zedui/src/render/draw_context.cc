#include "zedui/render/draw_context.h"

namespace zedui {

DrawContext::DrawContext(zedbase::RefPtr<PictureLayer> picture_layer)
    : picture_layer_(picture_layer) {}

void DrawContext::DrawCircle(float x, float y, float radius) {
  auto draw_command = std::make_shared<DrawCircleCommand>(x, y, radius);
  picture_layer_->PushDrawCommand(draw_command);
}

void DrawContext::DrawRectangle(float left,
                                float top,
                                float width,
                                float height) {
  auto draw_command =
      std::make_shared<DrawRectCommand>(left, top, width, height);
  picture_layer_->PushDrawCommand(draw_command);
}

}  // namespace zedui
