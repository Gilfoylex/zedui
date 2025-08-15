#include "zedbase/task_runner.h"
#include "zedui/app.h"
#include "zedui/geometry/rect.h"
#include "zedui/render/picture_layer.h"
#include "zedui/render/renderer.h"

namespace zedui {
PictureLayer::PictureLayer(float left, float top, float width, float height)
    : left_(left), top_(top), width_(width), height_(height) {}

zedui::PictureLayer::~PictureLayer() {
  auto key = reinterpret_cast<intptr_t>(this);
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
    std::unique_ptr<DrawCommand> command) {
  draw_commands_.push_back(std::move(command));
}

void PictureLayer::RenderToScreen(zedbase::WeakPtr<Renderer> renderer) {
  renderer_ = std::move(renderer);
  renderer_->ExecuteDrawCommands(reinterpret_cast<intptr_t>(this),
                                 Rect::MakeXYWH(left_, top_, width_, height_),
                                 draw_commands_);
}

}  // namespace zedui