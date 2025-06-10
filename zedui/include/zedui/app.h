#ifndef ZEDUI_APP_H_
#define ZEDUI_APP_H_

#include <memory>

#include "zedbase/macros.h"
#include "zedbase/thread.h"

namespace zedui {
class App {
 public:
  App();
  ~App();

 private:
  std::unique_ptr<zedbase::Thread> render_thread_;

  ZED_DISALLOW_COPY_ASSIGN_AND_MOVE(App);
};
}  // namespace zedui

#endif  // ZEDUI_APP_H_