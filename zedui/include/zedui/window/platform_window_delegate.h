#pragma once

namespace zedui {
class Event;
enum class PlatformWindowState {
  kUnknown,
  kMaximized,
  kMinimized,
  kNormal,
  kFullScreen,
};

class PlatformWindowDelegate {
 public:
  virtual ~PlatformWindowDelegate() = default;
  virtual void OnCreated() = 0;
  virtual void OnDestory() = 0;
  virtual void OnSizeChanged(int width, int height) = 0;
  virtual void DispatchEvent(Event* event) = 0;
  virtual void OnWindowStateChanged(PlatformWindowState old_state,
                                    PlatformWindowState new_state) = 0;
};

}  // namespace zedui