#pragma once

#include <memory>
#include "yoga/Yoga.h"
#include "zedbase/macros.h"
#include "zedbase/memory/ref_ptr.h"
#include "zedui/events/event_handler.h"
#include "zedui/events/event_target.h"
#include "zedui/geometry/rect.h"
#include "zedui/views/view_targeter.h"


namespace zedui {
class Widget;
class ContainerLayer;
class DrawContext;
class SceneBuilder;
class PictureLayer;

class View : public EventTarget, public EventHandler {
 public:
  using Views = std::vector<View*>;
  View();
  virtual ~View() override;

  View* GetParent() const;
  YGNodeRef GetNode() const;

  virtual const Widget* GetWidget() const;
  virtual Widget* GetWidget();
  std::unique_ptr<ViewTargeter> SetEventTargeter(
      std::unique_ptr<ViewTargeter> targeter);

  // Returns the ViewTargeter installed on |this| if one exists,
  // otherwise returns the ViewTargeter installed on our root view.
  // The return value is guaranteed to be non-null.
  ViewTargeter* GetEffectiveViewTargeter() const;

  // EventTarget overrides
  bool CanAcceptEvent(const Event& event) override;
  EventTarget* GetParentTarget() const override;
  EventTargeter* GetEventTargeter() override;

  ViewTargeter* targeter() const { return targeter_.get(); }

  float GetLeft() const;
  float GetTop() const;
  float GetRight() const;
  float GetBottom() const;
  float GetWidth() const;
  float GetHeight() const;

  void SetWidth(float width);
  void SetHeight(float height);
  Rect GetLocalBounds() const;

  bool IsVisible() const;

  template <typename T>
  T* AddChildViewRaw(T* view) {
    AddChildViewAtImpl(view, children_.size());
    return view;
  }
  template <typename T>
  T* AddChildViewAt(T* view, size_t index) {
    AddChildViewAtImpl(view, index);
    return view;
  }

  virtual void AddChildViewAtImpl(View* view, size_t index);
  void ReorderChildView(View* view, size_t index);

  template <typename T>
  std::unique_ptr<T> RemoveChildView(T* view) {
    ZED_DCHECK(zedbase::Contains(children_, view));
    DoRemoveChildView(view, false, nullptr);
    return zedbase::WrapUnique(view);
  }

  virtual void DoRemoveChildView(View* view,
                                 bool delete_removed_view,
                                 View* new_parent);

  Views::const_iterator FindChild(const View* view) const;

  void Invalidate();
  void MarkDirty();
  bool IsDirty() const;
  void DrawCompleted();
  virtual void BuildScene(SceneBuilder* scene_builder);
  virtual void OnDraw(DrawContext& draw_context);

  virtual zedbase::RefPtr<PictureLayer> GetPictureLayer();
  void ReCreatePictureLayer();

 protected:
  bool is_dirty_;
  YGNodeRef node_;
  Views children_;
  zedbase::RefPtr<PictureLayer> picture_layer_;
  View* parent_;
  std::unique_ptr<ViewTargeter> targeter_;
  bool visible_ = true;

  ZED_DISALLOW_COPY_ASSIGN_AND_MOVE(View);
};

}  // namespace zedui