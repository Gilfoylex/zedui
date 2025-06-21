#pragma once

#include <Windows.h>

namespace zedui {

UINT GetDpiForHWND(HWND hwnd);
UINT GetDpiForMonitor(HMONITOR monitor);

}  // namespace zedui