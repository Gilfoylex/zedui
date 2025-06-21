#pragma once

#include "zedui/controls/ui_container.h"

namespace zedui {
class Container : public UIContainer {
 public:
  Container();
  virtual void SetWidth(float width);
  virtual void SetHeight(float height);
  virtual void SetSize(const Size& size);
  void SetFlexDirection();
};
}  // namespace zedui