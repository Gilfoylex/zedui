#pragma once

#include <memory>
#include <vector>
#include "zedui/geometry/size.h"
#include "zedui/render/container_layer.h"
#include "zedui/render/draw_command.h"
#include "zedui/geometry/rect.h"

namespace zedui {
class Renderer : public std::enable_shared_from_this<Renderer> {
 public:
  virtual void CreateRenderTarget(Size size) = 0;
  virtual void ResizeRenderTarget(Size size) = 0;
  virtual void RenderFrame(std::shared_ptr<ContainerLayer> layer_tree) = 0;
  virtual void DestroyRenderTarget() = 0;
  virtual void ExecuteDrawCommands(
      Layer* key,
      Rect rect,
      const std::vector<std::shared_ptr<DrawCommand>>& commands) = 0;
  virtual void DeleteLayerCache(Layer* key) = 0;
  virtual ~Renderer() = default;
};

}  // namespace zedui