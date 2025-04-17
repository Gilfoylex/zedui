#ifndef ZEDUI_CONTROLS_CONTROL_H_
#define ZEDUI_CONTROLS_CONTROL_H_

#include <memory>

#include "yoga/Yoga.h"
#include "zedbase/macros.h"
#include "zedui/geometry/rect.h"
#include "zedui/geometry/size.h"
#include "zedui/render/draw_context.h"

namespace zedui {

class Control {
 public:
  Control();
  explicit Control(std::shared_ptr<Control> parent);
  virtual ~Control();
  std::shared_ptr<Control> GetParent() const;
  YGNodeRef GetNode() const;
  
  Rect GetRect() const;
  float GetWidth() const;
  void SetWidth(float width);
  float GetHeight() const;
  void SetHeight(float height);

 protected:
  virtual void Draw(const DrawContext& draw_context);
  virtual void OnSizeChanged(const Size& old_size, const Size& new_size);

 protected:
  std::weak_ptr<Control> parent_;
  YGNodeRef node_;

  ZED_DISALLOW_COPY_ASSIGN_AND_MOVE(Control);
};
}  // namespace zedui

#endif  // ZEDUI_CONTROLS_CONTROL_H_