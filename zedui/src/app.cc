#include "zedui/app.h"

namespace zedui {
App::App() {
  render_thread_ = std::make_unique<zedbase::Thread>("RenderThread");
  ui_task_runner_ = std::make_shared<zedbase::UITaskRunner>();
  vsync_timer_ = std::make_unique<zedbase::ThreadTimer>();
  vsync_timer_->Start(zedbase::TimeDelta::FromMilliseconds(16),
                      [this]() { OnVsync(); });
  App::Current = this;
}
App::~App() {
  App::Current = nullptr;
  vsync_timer_->Stop();
  ui_task_runner_.reset();
  if (render_thread_) {
    render_thread_->Join();
  }
}

std::shared_ptr<zedbase::UITaskRunner> App::GetUITaskRunner() {
  return ui_task_runner_;
}

}  // namespace zedui