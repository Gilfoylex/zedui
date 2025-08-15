#pragma once

#include "zedbase/macros.h"
#include "zedui/render/picture_layer.h"
#include "zedbase/memory/ref_ptr.h"

namespace zedui {
class DrawContext final {
 public:
  DrawContext(zedbase::RefPtr<PictureLayer> picture_layer);

  // draw methods
  void DrawCircle(float left, float top, float radius);
  void DrawRectangle(float left, float top, float width, float height);

 private:
  zedbase::RefPtr<PictureLayer> picture_layer_;

  ZED_DISALLOW_COPY_ASSIGN_AND_MOVE(DrawContext);
};

}  // namespace zedui
