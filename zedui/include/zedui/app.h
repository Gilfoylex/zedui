#pragma once

#include <memory>
#include <queue>
#include <mutex>

#include "zedbase/macros.h"
#include "zedbase/thread.h"
#include "zedbase/timer/timer.h"
#include "zedui/utils/ui_task_runner.h"


namespace zedui {
class App {
 public:
  static App* Current;

 public:
  App();
  ~App();
  std::shared_ptr<UITaskRunner> GetUITaskRunner();
  zedbase::RefPtr<zedbase::TaskRunner> GetRenderTaskRunner();
  void PostVsyncTask(zedbase::closure task);
  void Run();

 private:
  void OnVsync();

 private:
  std::unique_ptr<zedbase::Thread> render_thread_;
  std::shared_ptr<UITaskRunner> ui_task_runner_;
  std::unique_ptr<zedbase::ThreadTimer> vsync_timer_;
  std::mutex vsync_mutex_;
  std::queue<zedbase::closure> vsync_tasks_;

  ZED_DISALLOW_COPY_ASSIGN_AND_MOVE(App);
};

}  // namespace zedui