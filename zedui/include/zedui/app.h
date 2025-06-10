#ifndef ZEDUI_APP_H_
#define ZEDUI_APP_H_

#include <memory>
#include <queue>

#include "zedbase/macros.h"
#include "zedbase/thread.h"
#include "zedbase/timer/timer.h"
#include "zedbase/ui_task_runner.h"


namespace zedui {
class App {
 public:
  static App* Current;

 public:
  App();
  ~App();
  std::shared_ptr<zedbase::UITaskRunner> GetUITaskRunner();

 private:
  void OnVsync();

 private:
  std::unique_ptr<zedbase::Thread> render_thread_;
  std::shared_ptr<zedbase::UITaskRunner> ui_task_runner_;
  std::unique_ptr<zedbase::ThreadTimer> vsync_timer_;
  std::queue<zedbase::closure> vsync_tasks_;

  ZED_DISALLOW_COPY_ASSIGN_AND_MOVE(App);
};

}  // namespace zedui

#endif  // ZEDUI_APP_H_