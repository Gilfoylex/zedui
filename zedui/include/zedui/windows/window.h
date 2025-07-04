#pragma once

#include <memory>

#include "yoga/Yoga.h"

#include "zedbase/macros.h"

#include "zedui/controls/container.h"
#include "zedui/windows/win32_window.h"
#include "zedui/windows/window_delegate.h"
#include "zedui/render/renderer.h"

namespace zedui {

class Window : public WindowDelegate, public Container {
 public:
  Window();
  virtual ~Window();

  void Show();

  // WindowDelegate overrides
  void OnCreated() override;
  void OnDestroyed() override;
  void OnSizeChanged(int width, int height) override;

  // Container overrides
  void Build(std::shared_ptr<ContainerLayer> layer_tree) override;
  void NotifyParentForRedraw() override;
  void Draw(DrawContext& draw_context) override;
  void DrawCompleted() override;
  void SetWidth(float width) override;
  void SetHeight(float height) override;
  void SetSize(const Size& size) override;

  // UIElement overrides
  float GetWidth() const override;
  float GetHeight() const override;
  
 private:
  void DoFrame();

 private:
  Win32Window win32_window_;
  bool in_redraw_;
  bool created_;
  unsigned int width_ = 400;
  unsigned int height_ = 300;
  std::shared_ptr<Renderer> renderer_;
  ZED_DISALLOW_COPY_ASSIGN_AND_MOVE(Window);
};

}  // namespace zedui