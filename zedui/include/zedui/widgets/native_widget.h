#pragma once

#include <memory>
#include "zedbase/memory/weak_ptr.h"
#include "zedui/events/event_target.h"
#include "zedui/window/platform_window_delegate.h"

namespace zedui {
enum class WindowShowState;
class NativeWidgetDelegate;
class PlatformWindow;

class NativeWidget : public PlatformWindowDelegate, public EventTarget {
 public:
  virtual ~NativeWidget() override = default;
  static NativeWidget* CreateNativeWidget(NativeWidgetDelegate* delegate);

  void* GetNativeWidgetHandle();
  void Show(WindowShowState show_state);

  // EventTarget pure virtual function implementations
  bool CanAcceptEvent(const Event& event) override;
  EventTarget* GetParentTarget() const override;
  EventTargeter* GetEventTargeter() override;

  void OnCreated() override;
  void OnDestory() override;
  void OnSizeChanged(int width, int height) override;
  void DispatchEvent(Event* event) override;
  void OnWindowStateChanged(PlatformWindowState old_state,
                            PlatformWindowState new_state) override;

 protected:
  explicit NativeWidget(NativeWidgetDelegate* delegate);

 private:
  zedbase::WeakPtr<NativeWidgetDelegate> delegate_;
  std::unique_ptr<PlatformWindow> window_;
};

}  // namespace zedui
