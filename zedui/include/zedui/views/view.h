#pragma once

#include <memory>
#include "yoga/Yoga.h"
#include "zedbase/macros.h"
#include "zedui/events/event_handler.h"
#include "zedui/events/event_target.h"
#include "zedui/geometry/rect.h"
#include "zedui/views/container_view.h"

namespace zedui {

class PictureLayer;
class ContainerLayer;
class DrawContext;

class View : public EventTarget, public EventHandler {
 public:
  View();
  virtual ~View() override;

  ContainerView* GetParent() const;
  YGNodeRef GetNode() const;

  float GetLeft() const;
  float GetTop() const;
  float GetRight() const;
  float GetBottom() const;
  float GetWidth() const;
  float GetHeight() const;

  void SetWidth(float width);
  void SetHeight(float height);
  Rect GetLocalBounds() const;

 public:
  virtual std::shared_ptr<zedui::PictureLayer> GetPictureLayer();
  virtual void Invalidate();
  virtual void MarkDirty();
  virtual bool IsDirty() const;
  virtual void Build(std::shared_ptr<ContainerLayer> layer_tree);
  virtual void Draw(DrawContext& draw_context);
  virtual void DrawCompleted();

 protected:
  bool is_dirty_;
  YGNodeRef node_;

 private:
  friend class ContainerView;
  ContainerView* parent_;
  ZED_DISALLOW_COPY_ASSIGN_AND_MOVE(View);
};

}  // namespace zedui