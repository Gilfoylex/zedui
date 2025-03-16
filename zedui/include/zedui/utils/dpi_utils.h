#ifndef ZEDUI_UTILS_DPI_UTILS_H_
#define ZEDUI_UTILS_DPI_UTILS_H_

#include <Windows.h>

namespace zedui {
UINT GetDpiForHWND(HWND hwnd);
UINT GetDpiForMonitor(HMONITOR monitor);
}  // namespace zedui

#endif  // ZEDUI_UTILS_DPI_UTILS_H_