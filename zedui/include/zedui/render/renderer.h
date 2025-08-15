#pragma once

#include <memory>
#include <vector>
#include "zedbase/memory/weak_ptr.h"
#include "zedui/geometry/rect.h"
#include "zedui/geometry/size.h"
#include "zedui/render/container_layer.h"
#include "zedui/render/draw_command.h"

namespace zedui {
class Renderer {
 public:
  virtual void CreateRenderTarget(Size size) = 0;
  virtual void ResizeRenderTarget(Size size) = 0;
  virtual void RenderFrame(std::shared_ptr<ContainerLayer> layer_tree) = 0;
  virtual void DestroyRenderTarget() = 0;
  virtual void ExecuteDrawCommands(
      intptr_t key,
      Rect rect,
      const std::vector<std::unique_ptr<DrawCommand>>& commands) = 0;
  virtual void DeleteLayerCache(intptr_t key) = 0;
  virtual ~Renderer() = default;

 protected:
  zedbase::WeakPtr<Renderer> GetWeakPtr() {
    return weak_ptr_factory_.GetWeakPtr();
  }

 private:
  zedbase::WeakPtrFactory<Renderer> weak_ptr_factory_{this};
};

}  // namespace zedui