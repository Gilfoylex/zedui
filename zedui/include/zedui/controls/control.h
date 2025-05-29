#ifndef ZEDUI_CONTROLS_CONTROL_H_
#define ZEDUI_CONTROLS_CONTROL_H_

#include <memory>

#include "yoga/Yoga.h"
#include "zedbase/macros.h"
#include "zedui/geometry/rect.h"
#include "zedui/geometry/size.h"
#include "zedui/render/draw_context.h"
#include "zedui/render/layer.h"

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
  bool NeedRedraw() const;
  void DrawFinished();

 public:
  virtual std::shared_ptr<zedui::Layer> GetLayer();
  virtual void Draw(const DrawContext& draw_context);
  virtual void OnSizeChanged(const Size& old_size, const Size& new_size);

 protected:
  std::weak_ptr<Control> parent_;
  YGNodeRef node_;
  bool need_redraw_ = false;
  std::shared_ptr<zedui::Layer> layer_;

  ZED_DISALLOW_COPY_ASSIGN_AND_MOVE(Control);
};
}  // namespace zedui

#endif  // ZEDUI_CONTROLS_CONTROL_H_