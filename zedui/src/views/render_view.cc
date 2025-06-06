#include "zedui/views/render_view.h"

namespace zedui {
void zedui::RenderView::PerformLayout(float width,
                                      float height,
                                      YGDirection direction) {
  YGNodeCalculateLayout(node_, width, height, direction);
}

}  // namespace zedui
