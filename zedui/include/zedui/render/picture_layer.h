#pragma once

#include <memory>
#include <vector>
#include "zedui/render/draw_command.h"
#include "zedui/render/layer.h"

namespace zedui {

class PictureLayer final : public Layer {
 public:
  PictureLayer(float left, float top, float width, float height);
  ~PictureLayer();
  void PushDrawCommand(const std::shared_ptr<DrawCommand>& command);
  float GetLeft() const;
  float GetTop() const;
  float GetWidth() const;
  float GetHeight() const;

 public:
  void RenderToScreen(std::shared_ptr<Renderer> renderer) override;

 private:
  float left_;
  float top_;
  float width_;
  float height_;
  std::vector<std::shared_ptr<DrawCommand>> draw_commands_;
  std::shared_ptr<Renderer> renderer_;
};

}  // namespace zedui