#pragma once

#include "zedui/window/platform_window_delegate.h"
#include "zedui/window/window_tree_host.h"


namespace zedui {
class WindowTreeHostWin : public WindowTreeHost,
                          public PlatformWindowDelegate {};
}  // namespace zedui