#include "zedui/base/task_runner.h"
#include "zedui/base/time_point.h"
#include "zedui/base/utils.h"
#include "zedui/core/zedui_window.h"

#include <iostream>
#include <thread>


int APIENTRY wWinMain(_In_ HINSTANCE instance,
                      _In_opt_ HINSTANCE prev,
                      _In_ wchar_t* command_line,
                      _In_ int show_command) {
  // Attach to console when present (e.g., 'flutter run') or create a
  // new console when running with a debugger.
  if (!::AttachConsole(ATTACH_PARENT_PROCESS) && ::IsDebuggerPresent()) {
    zedui::CreateAndAttachConsole();
  }

  // Initialize COM, so that it is available for use in the library and/or
  // plugins.
  auto hr = ::CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
  if (FAILED(hr)) {
    return EXIT_FAILURE;
  }

  zedui::ZedUiWindow window;
  zedui::Win32Window::Point origin(10, 10);
  zedui::Win32Window::Size size(1280, 720);
  if (!window.Create(L"zedui_windows_app", origin, size)) {
    return EXIT_FAILURE;
  }
  window.SetQuitOnClose(true);

  ::MSG msg;
  while (::GetMessage(&msg, nullptr, 0, 0)) {
    ::TranslateMessage(&msg);
    ::DispatchMessage(&msg);
  }

  ::CoUninitialize();
  return EXIT_SUCCESS;
}