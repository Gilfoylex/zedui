#pragma once

#include "zedbase/macros.h"

namespace zedui {
class Layer {
 public:
  virtual ~Layer();
  virtual void RenderToScreen() = 0;
};
}  // namespace zedui