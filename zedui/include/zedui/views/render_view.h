#ifndef ZEDUI_VIEWS_RENDER_VIEW_H_
#define ZEDUI_VIEWS_RENDER_VIEW_H_

#include <memory>
#include "zedui/controls/container.h"

namespace zedui {
class RenderView : public Container {
 public:
  RenderView() = default;

  void Render();
private:
  
};

} // namespace zedui

#endif // ZEDUI_VIEWS_RENDER_VIEW_H_