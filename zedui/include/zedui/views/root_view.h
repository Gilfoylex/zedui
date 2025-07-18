#pragma once

#include <memory>
#include "zedui/views/container_view.h"

namespace zedui {
class ContainerLayer;
class RootViewDelegate {
 public:
  virtual ~RootViewDelegate() = default;
  virtual void TriggerRedraw() = 0;
};

class RootView : public ContainerView {
 public:
  RootView(RootViewDelegate* delegate);
  virtual ~RootView();
  std::shared_ptr<ContainerLayer> BuildLayerTree();

 public:
  void NotifyParentForRedraw() override;
  void Build(std::shared_ptr<ContainerLayer> layer_tree) override;

 private:
  RootViewDelegate* delegate_;
};
}  // namespace zedui