#pragma once

namespace zedui {
enum class WindowShowState;
class NativeWidgetPrivate {
 public:
  virtual ~NativeWidgetPrivate() = default;

  // static NativeWidgetPrivate* CreateNativeWidgetPrivate();

  // Destroys the native widget.
  // virtual void DestroyNativeWidget() = 0;

  // Returns the handle to the native widget.
  virtual void* GetNativeWidgetHandle() const = 0;
  virtual void Show(WindowShowState show_state) = 0;
  //virtual void Hide() = 0;
};

}  // namespace zedui