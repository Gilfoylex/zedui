#pragma once

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

  // Override UIElement methods
  void MarkDirty() override;
};
}  // namespace zedui