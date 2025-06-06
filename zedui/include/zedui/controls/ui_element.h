#ifndef ZEDUI_CONTROLS_UI_ELEMENT_H_
#define ZEDUI_CONTROLS_UI_ELEMENT_H_

#include <memory>

#include "yoga/Yoga.h"
#include "zedbase/macros.h"
#include "zedui/geometry/rect.h"
#include "zedui/geometry/size.h"
#include "zedui/render/draw_context.h"
#include "zedui/render/picture_layer.h"

namespace zedui {
class UIElement {
 public:
  UIElement();
  explicit UIElement(std::shared_ptr<UIElement> parent);
  virtual ~UIElement();
  std::shared_ptr<UIElement> GetParent() const;

  YGNodeRef GetNode() const;

  Rect GetRect() const;
  float GetWidth() const;
  void SetWidth(float width);
  float GetHeight() const;
  void SetHeight(float height);

 public:
  virtual std::shared_ptr<zedui::PictureLayer> GetPictureLayer();
  virtual void MarkDirty();
  virtual void Draw(const DrawContext& draw_context);
  virtual bool IsDirty() const;
  virtual void EndDraw();

 protected:
  std::weak_ptr<UIElement> parent_;
  YGNodeRef node_;
  bool is_dirty_ = false;
  std::shared_ptr<zedui::PictureLayer> picture_layer_;
 
  ZED_DISALLOW_COPY_ASSIGN_AND_MOVE(UIElement);
};

} // namespace zedui

#endif  // ZEDUI_CONTROLS_UI_ELEMENT_H_