#pragma once

#include <memory>

#include "yoga/Yoga.h"
#include "zedui/controls/ui_container.h"

namespace zedui {
class RenderView : public UIContainer {
 public:
  void PerformLayout(float width, float height, YGDirection direction);

 private:
};

}  // namespace zedui