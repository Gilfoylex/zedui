#pragma once

#include <memory>
#include <vector>
#include "zedbase/memory/weak_ptr.h"
#include "zedui/render/draw_command.h"
#include "zedui/render/layer.h"


namespace zedui {

class PictureLayer final : public Layer {
 public:
  PictureLayer(float left, float top, float width, float height);
  ~PictureLayer();
  void PushDrawCommand(std::unique_ptr<DrawCommand> command);
  float GetLeft() const;
  float GetTop() const;
  float GetWidth() const;
  float GetHeight() const;

 public:
  void RenderToScreen(zedbase::WeakPtr<Renderer> renderer) override;

 private:
  float left_;
  float top_;
  float width_;
  float height_;
  std::vector<std::unique_ptr<DrawCommand>> draw_commands_;
  zedbase::WeakPtr<Renderer> renderer_;
};

}  // namespace zedui