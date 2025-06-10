#ifndef ZEDUI_CONTROLS_CONTROL_H_
#define ZEDUI_CONTROLS_CONTROL_H_

#include <memory>
#include "zedui/controls/ui_element.h"
namespace zedui {
class Control : public UIElement {
 public:
  Control();
  explicit Control(std::shared_ptr<UIContainer> parent);
  virtual ~Control() = default;
  void SetWidth(float width);
  void SetHeight(float height);
};
}  // namespace zedui

#endif  // ZEDUI_CONTROLS_CONTROL_H_