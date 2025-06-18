#ifndef ZEDUI_RENDER_LAYER_H_
#define ZEDUI_RENDER_LAYER_H_

#include "zedbase/macros.h"

namespace zedui {
class Layer {
 public:
  virtual ~Layer();
  virtual void RenderToScreen() = 0;
};
}  // namespace zedui

#endif  // ZEDUI_RENDER_LAYER_H_