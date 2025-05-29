#ifndef ZEDUI_RENDER_DRAW_CONTEXT_H_
#define ZEDUI_RENDER_DRAW_CONTEXT_H_

#include <memory>

#include "zedui/render/layer.h"

namespace zedui {
class DrawContext {
 public:
  DrawContext(std::shared_ptr<Layer> layer) : layer_(layer) {};

  void DrawCircle(float x, float y, float radius) {
    // Implementation for drawing a circle using the layer
  }

  void DrawRectangle(float x, float y, float width, float height) {
    // Implementation for drawing a rectangle using the layer
  }

 private:
  std::shared_ptr<Layer> layer_;
};

}  // namespace zedui

#endif  // ZEDUI_RENDER_DRAW_CONTEXT_H_
