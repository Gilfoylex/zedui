#ifndef ZEDUI_CONTROLS_UI_CONTAINER_H_
#define ZEDUI_CONTROLS_UI_CONTAINER_H_

#include <list>
#include <memory>
#include "zedui/controls/ui_element.h"

namespace zedui {
class UIContainer : public UIElement {
 public:
  void Add(std::shared_ptr<UIElement> child);
  void Remove(std::shared_ptr<UIElement> child);

 public:
  void Draw(const DrawContext& draw_context) override;

 private:
  std::list<std::shared_ptr<UIElement>> childrens_;
};
}  // namespace zedui

#endif  // ZEDUI_CONTROLS_CONTAINER_H_