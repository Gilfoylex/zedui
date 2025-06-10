#ifndef ZEDUI_RENDER_DRAW_CONTEXT_H_
#define ZEDUI_RENDER_DRAW_CONTEXT_H_

#include <memory>
#include <stack>

#include "zedbase/macros.h"

#include "zedui/render/container_layer.h"
#include "zedui/render/picture_layer.h"

namespace zedui {
class DrawContext final {
 public:
  DrawContext();

  // draw methods
  void DrawCircle(float x, float y, float radius);
  void DrawRectangle(float x, float y, float width, float height);

  // layer management
  std::shared_ptr<ContainerLayer> GetLayerContainer() const;
  void AddLayerContainer(std::shared_ptr<ContainerLayer> layer_container);
  void PushPictureLayer(std::shared_ptr<PictureLayer> picture_layer);
  void PopPictureLayer();

 private:
  std::shared_ptr<ContainerLayer> layer_container_ = nullptr;
  std::stack<std::shared_ptr<PictureLayer>> picture_layers_;

  ZED_DISALLOW_COPY_ASSIGN_AND_MOVE(DrawContext);
};

}  // namespace zedui

#endif  // ZEDUI_RENDER_DRAW_CONTEXT_H_
