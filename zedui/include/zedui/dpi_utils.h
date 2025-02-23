#ifndef DPI_UTILS_H_
#define DPI_UTILS_H_

#include <Windows.h>

namespace zedui {
UINT GetDpiForHWND(HWND hwnd);
UINT GetDpiForMonitor(HMONITOR monitor);
}  // namespace zedui

#endif  // DPI_UTILS_H_