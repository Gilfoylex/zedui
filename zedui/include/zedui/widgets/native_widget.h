#pragma once

#include <memory>
#include "zedbase/memory/weak_ptr.h"
#include "zedui/widgets/native_widget_delegate.h"
#include "zedui/window/window_tree_host.h"

namespace zedui {
enum class WindowShowState;
class NativeWidget {
 public:
  explicit NativeWidget(NativeWidgetDelegate* delegate);
  void* GetNativeWidgetHandle() const;
  void Show(WindowShowState show_state);

  private:
   zedbase::WeakPtr<NativeWidgetDelegate> delegate_;
   std::unique_ptr<WindowTreeHost> host_;
};

}  // namespace zedui