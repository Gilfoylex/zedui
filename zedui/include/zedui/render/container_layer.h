#pragma once

#include <memory>
#include <vector>

#include "zedui/render/layer.h"

namespace zedui {
class ContainerLayer : public Layer {
 public:
  void Add(std::shared_ptr<Layer> layer);

 public:
  void RenderToScreen(std::shared_ptr<Renderer> renderer) override;

 protected:
  std::vector<std::shared_ptr<Layer>> child_layers_;
};

}  // namespace zedui