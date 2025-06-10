#include "zedui/app.h"

namespace zedui {
App::App() {
  render_thread_ = std::make_unique<zedbase::Thread>("RenderThread");
}
App::~App() {
  if (render_thread_) {
    render_thread_->Join();
  }
}

}  // namespace zedui