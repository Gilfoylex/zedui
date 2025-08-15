#pragma once
#include <memory>
#include <vector>
#include "zedbase/memory/ref_ptr.h"

namespace zedui {
class ContainerLayer;
class PictureLayer;
class SceneBuilder {
 public:
  SceneBuilder();
  void PushContainerLayer(zedbase::RefPtr<ContainerLayer> layer);
  void PushLayer(zedbase::RefPtr<Layer> layer);
  void PopContainerLayer();

 private:
  zedbase::RefPtr<ContainerLayer> root_layer_;
  zedbase::RefPtr<ContainerLayer> current_layer_;
  std::vector<zedbase::RefPtr<ContainerLayer>> layer_stack_;
};

}  // namespace zedui