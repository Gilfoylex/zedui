#pragma once
#include <memory>
#include "zedbase/macros.h"
#include "zedbase/memory/weak_ptr.h"
#include "zedui/events/event_source.h"
#include "zedui/render/renderer.h"
#include "zedui/views/root_view.h"
#include "zedui/widgets/native_widget.h"
#include "zedui/widgets/native_widget_delegate.h"


namespace zedui {
class Widget : public NativeWidgetDelegate,
               public EventSource,
               public RootViewDelegate {
 public:
  Widget();
  zedbase::WeakPtr<Widget> GetWeakPtr();
  std::shared_ptr<RootView> GetContentView() const;

  // RootViewDelegate overrides
  void TriggerRedraw() override;

  // NativeWidgetDelegate overrides
  Widget* AsWidget() override;
  const Widget* AsWidget() const override;
  void OnNativeWidgetCreated() override;
  void OnNativeWidgetDestroyed() override;
  void OnNativeWidgetSizeChanged(const Size& new_size) override;

  // EventSource overrides
  EventSink* GetEventSink() override;

 private:
  std::unique_ptr<NativeWidget> native_widget_;
  std::shared_ptr<RootView> root_view_;
  std::shared_ptr<Renderer> renderer_;
  zedbase::WeakPtrFactory<Widget> weak_ptr_factory_{this};
  ZED_DISALLOW_COPY_ASSIGN_AND_MOVE(Widget);
};
}  // namespace zedui