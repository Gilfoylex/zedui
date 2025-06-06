#ifndef ZEDUI_RENDER_CONTAINER_LAYER_H_
#define ZEDUI_RENDER_CONTAINER_LAYER_H_

#include <memory>
#include <vector>
#include "zedui/render/layer.h"

namespace zedui {
class ContainerLayer : public Layer {
 public:
  void Add(std::shared_ptr<Layer> layer);

 public:
  virtual void RenderToScreen() override;

 protected:
  std::vector<std::shared_ptr<Layer>> child_layers_;
};

}  // namespace zedui

#endif  // ZEDUI_RENDER_CONTAINER_LAYER_H_