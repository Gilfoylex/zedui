#pragma once

#include <memory>
#include <vector>

#include "zedbase/memory/ref_ptr.h"
#include "zedui/render/layer.h"

namespace zedui {
class ContainerLayer : public Layer {
 public:
  void Add(zedbase::RefPtr<Layer> layer);

 public:
  void RenderToScreen(zedbase::WeakPtr<Renderer> renderer) override;

 protected:
  std::vector<zedbase::RefPtr<Layer>> child_layers_;
};

}  // namespace zedui