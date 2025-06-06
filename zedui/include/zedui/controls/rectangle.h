#ifndef ZEDUI_CONTROLS_RECTANGLE_H_
#define ZEDUI_CONTROLS_RECTANGLE_H_

#include <memory>
#include "zedui/controls/control.h"

namespace zedui {
class Rectangle : public Control {
 public:
  Rectangle(std::shared_ptr<UIContainer> parent, float width, float height);
  void Draw(DrawContext& draw_context) override;
};
}  // namespace zedui

#endif  // ZEDUI_CONTROLS_RECTANGLE_H_