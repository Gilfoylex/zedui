#pragma once

#include <memory>
#include <unordered_map>

#include <d2d1.h>
#include <windows.h>
#include <wrl/client.h>

#include "zedbase/macros.h"
#include "zedbase/memory/thread_checker.h"
#include "zedui/geometry/rect.h"
#include "zedui/render/container_layer.h"
#include "zedui/render/renderer.h"

namespace zedui {

class D2DRenderer : public Renderer {
 public:
  explicit D2DRenderer(HWND hwnd);
  ~D2DRenderer() override = default;

 public:
  void CreateRenderTarget(Size size) override;
  void ResizeRenderTarget(Size size) override;
  void RenderFrame(std::shared_ptr<ContainerLayer> layer_tree) override;
  void DestroyRenderTarget() override;
  void ExecuteDrawCommands(
      intptr_t key,
      Rect rect,
      const std::vector<std::unique_ptr<DrawCommand>>& commands) override;
  void DeleteLayerCache(intptr_t key) override;

 private:
  void EnsureFactory();
  Microsoft::WRL::ComPtr<ID2D1Bitmap> GetLayerCache(intptr_t key);
  void CacheLayer(intptr_t key, Microsoft::WRL::ComPtr<ID2D1Bitmap> value);

 private:
  HWND hwnd_;
  Size render_size_;
  Microsoft::WRL::ComPtr<ID2D1Factory> d2d_factory_;
  Microsoft::WRL::ComPtr<ID2D1HwndRenderTarget> render_target_;
  std::unordered_map<intptr_t, Microsoft::WRL::ComPtr<ID2D1Bitmap>>
      layer_caches_;

  ZED_DECLARE_THREAD_CHECKER(thread_checker_);

  ZED_DISALLOW_COPY_ASSIGN_AND_MOVE(D2DRenderer);
};
}  // namespace zedui