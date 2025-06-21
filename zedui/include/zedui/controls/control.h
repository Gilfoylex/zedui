#pragma once

#include <memory>
#include "zedui/controls/ui_element.h"
#include "zedui/geometry/size.h"
namespace zedui {
class Control : public UIElement {
 public:
  Control();
  virtual ~Control();
  void SetWidth(float width);
  void SetHeight(float height);
  void SetSize(Size size);

  void SetFlexGrow(float flex_grow);
};
}  // namespace zedui