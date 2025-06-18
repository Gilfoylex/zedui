#include "zedui/render/picture_layer.h"

namespace zedui {
PictureLayer::PictureLayer(float left, float top, float width, float height)
    : left_(left), top_(top), width_(width), height_(height) {}

float PictureLayer::GetLeft() const {
  return left_;
}
float PictureLayer::GetTop() const {
  return top_;
}
float PictureLayer::GetWidth() const {
  return width_;
}
float PictureLayer::GetHeight() const {
  return height_;
}

void PictureLayer::PushDrawCommand(
    const std::shared_ptr<DrawCommand>& command) {
  draw_commands_.push_back(command);
}

void PictureLayer::RenderToScreen() {
  // todo on screen
}

}  // namespace zedui