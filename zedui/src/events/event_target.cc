#include "zedui/events/event_target.h"

#include <algorithm>

namespace zedui {

void EventTarget::AddPreTargetHandler(EventHandler* handler) {
  pre_target_list_.push_back(handler);
}

void EventTarget::RemovePreTargetHandler(EventHandler* handler) {
  auto find = std::ranges::find(pre_target_list_, handler);
  if (find != pre_target_list_.end()) {
    pre_target_list_.erase(find);
  }
}

void EventTarget::AddPostTargetHandler(EventHandler* handler) {
  post_target_list_.push_back(handler);
}

void EventTarget::RemovePostTargetHandler(EventHandler* handler) {
  auto find = std::ranges::find(post_target_list_, handler);
  if (find != post_target_list_.end()) {
    post_target_list_.erase(find);
  }
}

}  // namespace zedui