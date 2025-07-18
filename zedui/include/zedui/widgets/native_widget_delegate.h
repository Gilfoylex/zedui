#pragma once

namespace zedui {
class Size;
class Widget;
class NativeWidgetDelegate {
 public:
  virtual ~NativeWidgetDelegate() = default;
  virtual Widget* AsWidget() = 0;
  virtual const Widget* AsWidget() const = 0;
  //   virtual bool IsNativeWidgetInitialized() const = 0;
  virtual void OnNativeWidgetCreated() = 0;
  // virtual void OnNativeWidgetDestroying() = 0;
  virtual void OnNativeWidgetDestroyed() = 0;
  //   virtual void OnNativeWidgetMove() = 0;
  virtual void OnNativeWidgetSizeChanged(const Size& new_size) = 0;
  //  virtual void OnNativeWidgetWindowShowStateChanged() = 0;
};

}  // namespace zedui