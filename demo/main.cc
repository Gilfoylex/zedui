#include "zedui/app.h"
#include "zedui/windows/window.h"

int main(int argc, char** argv) {
  zedui::App app;
  auto window = std::make_shared<zedui::Window>();
  window->Show();
  app.Run();
  return 0;
}