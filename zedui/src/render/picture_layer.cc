#include "zedui/render/picture_layer.h"
#include "zedbase/task_runner.h"
#include "zedui/app.h"
#include "zedui/render/renderer.h"
#include "zedui/geometry/rect.h"


namespace zedui {
PictureLayer::PictureLayer(float left, float top, float width, float height)
    : left_(left), top_(top), width_(width), height_(height) {}

zedui::PictureLayer::~PictureLayer() {
  auto key = this;
  zedbase::TaskRunner::RunNowOrPostTask(
      App::Current->GetRenderTaskRunner(),
      [renderer = std::move(renderer_), key]() {
        if (!renderer) {
          return;
        }
        renderer->DeleteLayerCache(key);
      });
}

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

void PictureLayer::RenderToScreen(std::shared_ptr<Renderer> renderer) {
  renderer_ = renderer;
  renderer->ExecuteDrawCommands(this, Rect::MakeXYWH(left_, top_, width_, height_), draw_commands_);
}

}  // namespace zedui