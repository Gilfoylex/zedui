#ifndef ZEDUI_CONTROLS_CONTAINER_H_
#define ZEDUI_CONTROLS_CONTAINER_H_

#include <list>
#include "zedui/controls/control.h"

namespace zedui {
class Container : public Control {
 public:
  void AddChild(std::shared_ptr<Control> child);
  void RemoveChild(std::shared_ptr<Control> child);
  const std::list<std::shared_ptr<Control>>& GetChildrens() const;

 private:
  std::list<std::shared_ptr<Control>> childrens_;
};
}  // namespace zedui

#endif  // ZEDUI_CONTROLS_CONTAINER_H_