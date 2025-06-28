#pragma once

#include <memory>
#include <stack>

#include "zedbase/macros.h"
#include "zedui/render/picture_layer.h"

namespace zedui {
class DrawContext final {
 public:
  DrawContext(float left,
              float top,
              std::shared_ptr<zedui::PictureLayer> picture_layer);

  // draw methods
  void DrawCircle(float left, float top, float radius);
  void DrawRectangle(float left, float top, float width, float height);

 private:
  float left_offset_;
  float top_offset_;
  std::shared_ptr<zedui::PictureLayer> picture_layer_;

  ZED_DISALLOW_COPY_ASSIGN_AND_MOVE(DrawContext);
};

}  // namespace zedui
