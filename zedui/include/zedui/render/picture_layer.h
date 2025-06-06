#ifndef ZEDUI_RENDER_PICTURE_LAYER_H_
#define ZEDUI_RENDER_PICTURE_LAYER_H_

#include "zedui/render/layer.h"

namespace zedui {
class PictureLayer : public Layer {
 public:
  virtual void RenderToScreen() override;
};
}  // namespace zedui

#endif  // ZEDUI_RENDER_PICTURE_LAYER_H_