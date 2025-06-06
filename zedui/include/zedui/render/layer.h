#ifndef ZEDUI_RENDER_LAYER_H_
#define ZEDUI_RENDER_LAYER_H_

#include "zedbase/macros.h"

namespace zedui {
class Layer {
 public:
  virtual void RenderToScreen() = 0;

  ZED_DISALLOW_COPY_ASSIGN_AND_MOVE(Layer);
};
}  // namespace zedui

#endif  // ZEDUI_RENDER_LAYER_H_