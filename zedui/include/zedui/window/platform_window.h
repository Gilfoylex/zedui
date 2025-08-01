#pragma once

namespace zedui {
enum class PlatformWindowState;
class PlatformWindow {
 public:
  virtual ~PlatformWindow() = default;
  virtual void Show(bool inactive = false) = 0;
  virtual void Hide() = 0;
  virtual void Close() = 0;
  virtual PlatformWindowState GetPlatformWindowState() const = 0;
  virtual void SetFullscreen(bool fullscreen) = 0;
  virtual void Maximize() = 0;
  virtual void Minimize() = 0;
  virtual void Restore() = 0;
  virtual void* GetWinwindowHandle() const = 0;
};

}  // namespace zedui