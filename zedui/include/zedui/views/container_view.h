#pragma once
#include <list>
#include <memory>
#include "zedui/views/view.h"
#include "zedui/render/picture_layer.h"

namespace zedui {
class ContainerView : public View,
                      public std::enable_shared_from_this<ContainerView> {
 public:
  ContainerView();
  virtual ~ContainerView();
  virtual void AddChild(std::shared_ptr<View> child);
  virtual void RemoveChild(std::shared_ptr<View> child);
  virtual void NotifyParentForRedraw();
  std::shared_ptr<PictureLayer> GetPictureLayer();

  void Invalidate() override;
  void MarkDirty() override;
  void Build(std::shared_ptr<ContainerLayer> layer_tree) override;

 protected:
  std::list<std::shared_ptr<View>> childrens_;
  std::shared_ptr<PictureLayer> picture_layer_;
};
}  // namespace zedui