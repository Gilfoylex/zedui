#ifndef ZEDUI_CONTROLS_UI_ELEMENT_H_
#define ZEDUI_CONTROLS_UI_ELEMENT_H_

#include <memory>

#include "yoga/Yoga.h"
#include "zedbase/macros.h"
#include "zedui/geometry/rect.h"
#include "zedui/geometry/size.h"
#include "zedui/render/draw_context.h"
#include "zedui/render/container_layer.h"

namespace zedui {
class UIContainer;  // Forward declaration for UIContainer
class UIElement {
 public:
  UIElement();
  explicit UIElement(std::shared_ptr<UIContainer> parent);
  virtual ~UIElement();
  std::shared_ptr<UIContainer> GetParent() const;
  YGNodeRef GetNode() const;

  float GetLeft() const;
  float GetTop() const;
  float GetWidth() const;
  float GetHeight() const;
  Rect GetRect() const;
  Size GetSize() const;

  virtual void Invalidate();
  virtual void MarkDirty();
  virtual bool IsDirty() const;
  virtual void Build(std::shared_ptr<ContainerLayer> layer_tree);
  virtual void Draw(DrawContext& draw_context);
  virtual void DrawCompleted();

 protected:
  std::weak_ptr<UIContainer> parent_;
  YGNodeRef node_;
  bool is_dirty_ = false;
  Rect last_render_rect_;

  ZED_DISALLOW_COPY_ASSIGN_AND_MOVE(UIElement);
};

}  // namespace zedui

#endif  // ZEDUI_CONTROLS_UI_ELEMENT_H_