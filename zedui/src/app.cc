#include <Windows.h>

#include "zedui/app.h"

namespace zedui {

App* App::Current = nullptr;
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

void App::PostVsyncTask(zedbase::closure task) {
  std::lock_guard<std::mutex> lock(vsync_mutex_);
  vsync_tasks_.push(std::move(task));
}

void App::OnVsync() {
  std::queue<zedbase::closure> tasks;
  {
    std::lock_guard<std::mutex> lock(vsync_mutex_);
    std::swap(tasks, vsync_tasks_);
  }

  if (tasks.empty()) {
    return;
  }

  while (!tasks.empty()) {
    ui_task_runner_->PostTask(std::move(tasks.front()));
    tasks.pop();
  }
}

void App::Run() {
  MSG msg;
  while (::GetMessage(&msg, nullptr, 0, 0)) {
    ::TranslateMessage(&msg);
    ::DispatchMessage(&msg);
  }
}

}  // namespace zedui