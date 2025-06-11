#ifndef ZEDUI_CONTROLS_CONTAINER_H_
#define ZEDUI_CONTROLS_CONTAINER_H_

#include "zedui/controls/ui_container.h"

namespace zedui {
class Container : public UIContainer {
 public:
  Container();
  explicit Container(std::shared_ptr<UIContainer> parent);
  void SetWidth(float width);
  void SetHeight(float height);

  void Draw(DrawContext& draw_context) override;
};
}  // namespace zedui

#endif  // ZEDUI_CONTROLS_CONTAINER_H_