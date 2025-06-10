#ifndef ZEDUI_CONTROLS_UI_CONTAINER_H_
#define ZEDUI_CONTROLS_UI_CONTAINER_H_

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
  void Draw(DrawContext& draw_context) override;

 public:
  virtual std::shared_ptr<zedui::PictureLayer> GetPictureLayer();
  virtual void NotifyParentForRedraw();

 protected:
  std::list<std::shared_ptr<UIElement>> childrens_;
  std::shared_ptr<zedui::PictureLayer> picture_layer_;
};
}  // namespace zedui

#endif  // ZEDUI_CONTROLS_CONTAINER_H_