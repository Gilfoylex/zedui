#pragma once

#include <memory>
#include "zedbase/macros.h"

namespace zedui {
class Renderer;
class Layer {
 public:
  virtual ~Layer();
  virtual void RenderToScreen(const std::shared_ptr<Renderer>& renderer) = 0;
};
}  // namespace zedui