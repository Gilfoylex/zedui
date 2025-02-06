#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include <vector>

namespace zedui {
  void CreateAndAttachConsole();
  std::string Utf8FromUtf16(const wchar_t* utf16_string);
  std::vector<std::string> GetCommandLineArguments();
  void ResyncOutputStreams();
} // namespace zedui

#endif  // UTILS_H_