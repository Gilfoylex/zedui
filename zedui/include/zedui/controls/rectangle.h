#pragma once

#include <memory>
#include "zedui/controls/control.h"

namespace zedui {
class Rectangle : public Control {
 public:
 Rectangle();
  explicit Rectangle(float width, float height);
  void Draw(DrawContext& draw_context) override;
};
}  // namespace zedui