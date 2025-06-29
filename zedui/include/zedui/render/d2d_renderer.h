#pragma once

#include <memory>
#include <unordered_map>

#include <d2d1.h>
#include <windows.h>
#include <wrl/client.h>

#include "zedui/render/container_layer.h"
#include "zedui/render/renderer.h"
#include "zedui/geometry/rect.h"

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
      Layer* key,
      Rect rect,
      const std::vector<std::shared_ptr<DrawCommand>>& commands) override;
  void DeleteLayerCache(Layer* key) override;

 private:
  void EnsureFactory();
  Microsoft::WRL::ComPtr<ID2D1Bitmap> GetLayerCache(Layer* key);
  void CacheLayer(Layer* key, Microsoft::WRL::ComPtr<ID2D1Bitmap> value);

 private:
  HWND hwnd_;
  Size render_size_;
  Microsoft::WRL::ComPtr<ID2D1Factory> d2d_factory_;
  Microsoft::WRL::ComPtr<ID2D1HwndRenderTarget> render_target_;
  std::unordered_map<Layer*, Microsoft::WRL::ComPtr<ID2D1Bitmap>>
      layer_caches_;
};
}  // namespace zedui