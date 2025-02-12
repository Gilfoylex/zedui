#include "graphics.h"

namespace zedui {

Graphics::Graphics() {}

Graphics::~Graphics() {
  factory_.Reset();
  render_target_.Reset();
}

bool Graphics::Initialize(HWND window) {
  render_thread_ = std::thread([this, window]() {
    D2D1_FACTORY_OPTIONS options;
    ZeroMemory(&options, sizeof(D2D1_FACTORY_OPTIONS));

    HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, options,
                                   factory_.GetAddressOf());
    if (FAILED(hr)) {
      return false;
    }

    RECT rect;
    GetClientRect(window, &rect);

    hr = factory_->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(window,
                                         D2D1::SizeU(rect.right, rect.bottom)),
        render_target_.GetAddressOf());
    if (FAILED(hr)) {
      return false;
    }

    while (true) {
      std::this_thread::sleep_for(std::chrono::milliseconds(16));
      BeginDraw();
      ClearScreen(255.0f, 255.0f, 255.0f);
      DrawCircle(100.0f, 100.0f, 50.0f, 1.0f, 0.0f, 0.0f, 1.0f);
      EndDraw();
    }
  });

  /*D2D1_FACTORY_OPTIONS options;
  ZeroMemory(&options, sizeof(D2D1_FACTORY_OPTIONS));

  HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, options,
                                 factory_.GetAddressOf());
  if (FAILED(hr)) {
    return false;
  }

  RECT rect;
  GetClientRect(window, &rect);

  hr = factory_->CreateHwndRenderTarget(
      D2D1::RenderTargetProperties(),
      D2D1::HwndRenderTargetProperties(window,
                                       D2D1::SizeU(rect.right, rect.bottom)),
      render_target_.GetAddressOf());
  if (FAILED(hr)) {
    return false;
  }*/

  return true;
}

void Graphics::BeginDraw() {
  render_target_->BeginDraw();
}

void Graphics::EndDraw() {
  render_target_->EndDraw();
}

void Graphics::ClearScreen(float r, float g, float b) {
  render_target_->Clear(D2D1::ColorF(r, g, b));
}

void Graphics::DrawCircle(float x,
                          float y,
                          float radius,
                          float r,
                          float g,
                          float b,
                          float a) {
  ComPtr<ID2D1SolidColorBrush> brush;
  render_target_->CreateSolidColorBrush(D2D1::ColorF(r, g, b, a),
                                        brush.GetAddressOf());
  render_target_->DrawEllipse(
      D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), brush.Get(), 3.0f);
}

}  // namespace zedui