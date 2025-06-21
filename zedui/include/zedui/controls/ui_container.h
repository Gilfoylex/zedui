#pragma once

#include <list>
#include <memory>
#include "zedui/controls/ui_element.h"

namespace zedui {
class UIContainer : public UIElement {
 public:
  UIContainer();
  explicit UIContainer(std::shared_ptr<UIContainer> parent);
  void Add(std::shared_ptr<UIElement> child);
  void Remove(std::shared_ptr<UIElement> child);

 public:
  std::shared_ptr<zedui::PictureLayer> GetPictureLayer() override;
  void Invalidate() override;
  void MarkDirty() override;
  void Build(std::shared_ptr<ContainerLayer> layer_tree) override;
  void Draw(DrawContext& draw_context) override;

 public:
  virtual void NotifyParentForRedraw();

 protected:
  std::list<std::shared_ptr<UIElement>> childrens_;
  std::shared_ptr<zedui::PictureLayer> picture_layer_;
};
}  // namespace zedui