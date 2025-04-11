#pragma once

#include "zedui/render/draw_context.h"

namespace zedui {
class Visual {
  virtual void Draw(DrawContext* context) = 0;
};

}  // namespace zedui