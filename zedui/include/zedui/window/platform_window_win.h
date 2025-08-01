#pragma once

#include <Windows.h>

#include <functional>
#include <memory>
#include <string>

#include "zedbase/macros.h"
#include "zedui/window/platform_window_delegate.h"

namespace zedui {
class PlatformWindowWin {
 public:
  struct Point {
    unsigned int x;
    unsigned int y;
    Point(unsigned int x, unsigned int y) : x(x), y(y) {}
  };

  struct Size {
    unsigned int width;
    unsigned int height;
    Size(unsigned int width, unsigned int height)
        : width(width), height(height) {}
  };

  PlatformWindowWin(PlatformWindowDelegate* delegate);
  virtual ~PlatformWindowWin();

  bool Create(const std::wstring& title, const Point& origin, const Size& size);
  bool Show();
  void Destroy();
  HWND GetHandle();
  void SetQuitOnClose(bool quit_on_close);
  RECT GetClientArea();

 protected:
  virtual LRESULT MessageHandler(HWND window,
                                 UINT const message,
                                 WPARAM const wparam,
                                 LPARAM const lparam) noexcept;
  virtual bool OnCreate();
  virtual void OnDestroy();

 private:
  friend class WindowClassRegistrar;
  static LRESULT CALLBACK WndProc(HWND const window,
                                  UINT const message,
                                  WPARAM const wparam,
                                  LPARAM const lparam) noexcept;
  static PlatformWindowWin* GetThisFromHandle(HWND const window) noexcept;
  static void UpdateTheme(HWND const window);
  PlatformWindowDelegate* delegate_;
  bool quit_on_close_ = false;
  HWND window_handle_ = nullptr;

  ZED_DISALLOW_COPY_ASSIGN_AND_MOVE(PlatformWindowWin);
};

} // namespace zedui