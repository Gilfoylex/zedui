#pragma once
#include "zedui/events/event_source.h"

namespace zedui {
enum class PlatformWindowState;
class PlatformWindow : public EventSource {
 public:
  virtual ~PlatformWindow() override = default;
  virtual bool Show() = 0;
  virtual void Hide() = 0;
  virtual void Destroy() = 0;
  //virtual PlatformWindowState GetPlatformWindowState() const = 0;
  //virtual void SetFullscreen(bool fullscreen) = 0;
  //virtual void Maximize() = 0;
  //virtual void Minimize() = 0;
  //virtual void Restore() = 0;
  virtual void* GetWinwindowHandle() const = 0;
};

}  // namespace zedui