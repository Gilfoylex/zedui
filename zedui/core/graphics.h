#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <Windows.h>
#include <d2d1.h>
#include <wrl/client.h>

#include <thread>

namespace zedui {

using Microsoft::WRL::ComPtr;
class Graphics {
 public:
  Graphics();
  ~Graphics();
  bool Initialize(HWND window);
  void BeginDraw();
  void EndDraw();
  void ClearScreen(float r, float g, float b);
  void DrawCircle(float x,
                  float y,
                  float radius,
                  float r,
                  float g,
                  float b,
                  float a);

 private:
  ComPtr<ID2D1Factory> factory_;
  ComPtr<ID2D1HwndRenderTarget> render_target_;
  std::thread render_thread_;
};

}  // namespace zedui

#endif  // GRAPHICS_H_