#ifndef ZEDUI_CONTROLS_CONTAINER_H_
#define ZEDUI_CONTROLS_CONTAINER_H_

#include <list>
#include "zedui/controls/ui_element.h"

namespace zedui {
class Container : public UIElement {
 public:
  void AddChild(std::shared_ptr<UIElement> child);
  void RemoveChild(std::shared_ptr<UIElement> child);
  const std::list<std::shared_ptr<UIElement>>& GetChildrens() const;

 private:
  std::list<std::shared_ptr<UIElement>> childrens_;
};
}  // namespace zedui

#endif  // ZEDUI_CONTROLS_CONTAINER_H_