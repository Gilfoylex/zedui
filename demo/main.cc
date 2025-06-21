#include "zedui/app.h"
#include "zedui/windows/window.h"
#include "zedui/controls/rectangle.h"

int main(int argc, char** argv) {
  zedui::App app;
  auto window = std::make_shared<zedui::Window>();
  for (auto i =0; i < 10; i++){
    auto rectangle = std::make_shared<zedui::Rectangle>(50.0f, 50.0f);
    window->Add(rectangle);
  }
  window->Show();
  app.Run();
  return 0;
}