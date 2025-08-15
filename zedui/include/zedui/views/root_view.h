#pragma once

#include <memory>
#include "zedui/events/event_processor.h"
#include "zedui/views/view.h"

namespace zedui {
class ContainerLayer;
class RootView : public EventProcessor, public View {
 public:
  RootView();
  virtual ~RootView();

  // EventSink overrides
  void OnEventFromSource(Event* event) override;

  // View overrides
  void BuildScene(SceneBuilder* scene_builder) override;

 private:
};
}  // namespace zedui