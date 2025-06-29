#pragma once

#include <memory>

namespace zedui {

class Renderer;
class Layer {
 public:
  virtual ~Layer() = default;
  virtual void RenderToScreen(std::shared_ptr<Renderer> renderer) = 0;
};

}  // namespace zedui