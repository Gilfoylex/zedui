#include "zedui/render/d2d_renderer.h"

namespace zedui {

D2DRenderer::D2DRenderer(HWND hwnd) : hwnd_(hwnd) {}

void D2DRenderer::EnsureFactory() {
  ZED_DCHECK_CREATION_THREAD_IS_CURRENT(thread_checker_);
  if (!d2d_factory_) {
    D2D1_FACTORY_OPTIONS options = {};
#ifdef _DEBUG
    options.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
#endif
    auto hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, options,
                                d2d_factory_.GetAddressOf());
    if (FAILED(hr)) {
      // todo
    }
  }
}

void D2DRenderer::CreateRenderTarget(Size size) {
  EnsureFactory();
  RECT rc;
  GetClientRect(hwnd_, &rc);
  D2D1_RENDER_TARGET_PROPERTIES rt_props = D2D1::RenderTargetProperties();
  D2D1_HWND_RENDER_TARGET_PROPERTIES hwnd_props =
      D2D1::HwndRenderTargetProperties(
          hwnd_, D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top));

  auto hr = d2d_factory_->CreateHwndRenderTarget(
      rt_props, hwnd_props, render_target_.ReleaseAndGetAddressOf());
  if (FAILED(hr)) {
    return;
  }

  render_size_ = size;
}

void D2DRenderer::ResizeRenderTarget(Size size) {
  ZED_DCHECK_CREATION_THREAD_IS_CURRENT(thread_checker_);
  if (render_target_) {
    RECT rc;
    GetClientRect(hwnd_, &rc);
    auto size_u = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);
    render_target_->Resize(size_u);
    render_size_ = size;
  }
}

void D2DRenderer::RenderFrame(std::shared_ptr<ContainerLayer> layer_tree) {
  ZED_DCHECK_CREATION_THREAD_IS_CURRENT(thread_checker_);
  if (!render_target_)
    return;

  render_target_->BeginDraw();
  render_target_->Clear(D2D1::ColorF(D2D1::ColorF::Red));

  if (layer_tree) {
    layer_tree->RenderToScreen(shared_from_this());
  }

  HRESULT hr = render_target_->EndDraw();
  if (FAILED(hr)) {
    // 检查是否需要重建
    if (hr == D2DERR_RECREATE_TARGET) {
      render_target_.Reset();
      CreateRenderTarget(render_size_);
    }
  }
}

void D2DRenderer::DestroyRenderTarget() {
  render_target_.Reset();
}

void D2DRenderer::ExecuteDrawCommands(
    intptr_t key,
    Rect rect,
    const std::vector<std::shared_ptr<DrawCommand>>& commands) {
  ZED_DCHECK_CREATION_THREAD_IS_CURRENT(thread_checker_);

  auto cache_bitmap = GetLayerCache(key);
  D2D1_RECT_F bitmap_rect = D2D1::RectF(rect.GetMinX(), rect.GetMinY(),
                                        rect.GetMaxX(), rect.GetMaxY());
  if (cache_bitmap) {
    render_target_->DrawBitmap(cache_bitmap.Get(), bitmap_rect);
    return;
  }

  Microsoft::WRL::ComPtr<ID2D1BitmapRenderTarget> bitmap_rt;
  auto hr = render_target_->CreateCompatibleRenderTarget(
      D2D1::SizeF(rect.size.width, rect.size.height), &bitmap_rt);
  bitmap_rt->BeginDraw();
  Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> brush;
  bitmap_rt->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Blue), &brush);
  for (const auto& command : commands) {
    if (command->type == DrawType::Rect) {
      auto rectCommandPtr = std::dynamic_pointer_cast<DrawRectCommand>(command);
      D2D1_RECT_F rect =
          D2D1::RectF(rectCommandPtr->left, rectCommandPtr->top,
                      rectCommandPtr->right, rectCommandPtr->bottom);
      // render_target_->DrawRectangle(rect, brush.Get(), 3.0f);
      bitmap_rt->FillRectangle(rect, brush.Get());
    }
  }

  bitmap_rt->EndDraw();
  bitmap_rt->GetBitmap(&cache_bitmap);
  render_target_->DrawBitmap(cache_bitmap.Get(), bitmap_rect);
  CacheLayer(key, cache_bitmap);
}

void zedui::D2DRenderer::DeleteLayerCache(intptr_t key) {
  ZED_DCHECK_CREATION_THREAD_IS_CURRENT(thread_checker_);
  if (layer_caches_.empty()) {
    return;
  }

  layer_caches_.erase(key);
}

Microsoft::WRL::ComPtr<ID2D1Bitmap> D2DRenderer::GetLayerCache(intptr_t key) {
  ZED_DCHECK_CREATION_THREAD_IS_CURRENT(thread_checker_);
  if (layer_caches_.empty()) {
    return nullptr;
  }

  auto it = layer_caches_.find(key);
  if (it == layer_caches_.end()) {
    return nullptr;
  }

  return it->second;
}

void zedui::D2DRenderer::CacheLayer(intptr_t key,
                                    Microsoft::WRL::ComPtr<ID2D1Bitmap> value) {
  ZED_DCHECK_CREATION_THREAD_IS_CURRENT(thread_checker_);
  layer_caches_[key] = value;
}

}  // namespace zedui