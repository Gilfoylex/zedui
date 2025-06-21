#pragma once

#include <memory>
#include <vector>

#include <d2d1.h>
#include <windows.h>
#include <wrl/client.h>

#include "zedui/render/renderer.h"

namespace zedui {

class D2DRenderer : public Renderer {
 public:
  D2DRenderer(HWND hwnd);

 public:
  void CreateRenderTarget(Size size) override;
  void ResizeRenderTarget(Size size) override;
  void RenderFrame(std::shared_ptr<ContainerLayer> layer_tree) override;
  void DestroyRenderTarget() override;
  void ExecuteDrawCommands(
      const std::vector<std::shared_ptr<DrawCommand>>& commands) override;

 private:
  void EnsureFactory();

 private:
  HWND hwnd_;
  Size render_size_;
  Microsoft::WRL::ComPtr<ID2D1Factory> d2d_factory_;
  Microsoft::WRL::ComPtr<ID2D1HwndRenderTarget> render_target_;
};
}  // namespace zedui