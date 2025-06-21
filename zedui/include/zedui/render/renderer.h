#pragma once

#include <memory>
#include <vector>
#include "zedui/geometry/size.h"
#include "zedui/render/draw_command.h"

namespace zedui {
class ContainerLayer;
class Renderer : public std::enable_shared_from_this<Renderer> {
 public:
  virtual void CreateRenderTarget(Size size) = 0;
  virtual void ResizeRenderTarget(Size size) = 0;
  virtual void RenderFrame(std::shared_ptr<ContainerLayer> layer_tree) = 0;
  virtual void DestroyRenderTarget() = 0;
  virtual void ExecuteDrawCommands(
      const std::vector<std::shared_ptr<DrawCommand>>& commands) = 0;
  virtual ~Renderer() = default;
};

}  // namespace zedui