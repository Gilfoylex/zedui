#pragma once

namespace zedui {
class WindowDelegate {
 public:
  virtual void OnCreated() = 0;
  virtual void OnDestroyed() = 0;
  virtual void OnSizeChanged(int width, int height) = 0;
};
}  // namespace zedui