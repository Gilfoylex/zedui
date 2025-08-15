#include "zedbase/logging.h"
#include "zedui/render/container_layer.h"
#include "zedui/render/draw_context.h"
#include "zedui/render/picture_layer.h"
#include "zedui/render/scene_builder.h"
#include "zedui/views/view.h"
#include "zedui/widgets/widget.h"

namespace zedui {
View::View() : node_(YGNodeNew()), is_dirty_(true) {}
View::~View() {
  if (parent_) {
    parent_->RemoveChildView(this);
  }

  for (View* child : children_) {
    child->parent_ = nullptr;
    delete child;
  }
  children_.clear();

  if (node_) {
    YGNodeFree(node_);
  }
}

View* View::GetParent() const {
  return parent_;
}

YGNodeRef View::GetNode() const {
  return node_;
}

const Widget* View::GetWidget() const {
  // The root view holds a reference to this view hierarchy's Widget.
  return parent_ ? parent_->GetWidget() : nullptr;
}

Widget* View::GetWidget() {
  return const_cast<Widget*>(const_cast<const View*>(this)->GetWidget());
}

float View::GetLeft() const {
  return YGNodeLayoutGetLeft(node_);
}

float View::GetTop() const {
  return YGNodeLayoutGetTop(node_);
}

float View::GetRight() const {
  return YGNodeLayoutGetRight(node_);
}

float View::GetBottom() const {
  return YGNodeLayoutGetBottom(node_);
}

float View::GetWidth() const {
  return YGNodeLayoutGetWidth(node_);
}

float View::GetHeight() const {
  return YGNodeLayoutGetHeight(node_);
}

void View::SetWidth(float width) {
  YGNodeStyleSetWidth(node_, width);
  Invalidate();
}

void View::SetHeight(float height) {
  YGNodeStyleSetHeight(node_, height);
  Invalidate();
}

Rect View::GetLocalBounds() const {
  return Rect::MakeXYWH(GetLeft(), GetTop(), GetWidth(), GetHeight());
}

bool View::IsVisible() const {
  return visible_ && parent_ ? parent_->IsVisible() : false;
}

zedbase::RefPtr<PictureLayer> View::GetPictureLayer() {
  if (picture_layer_) {
    return picture_layer_;
  }

  ZED_DCHECK(GetParent());
  return GetParent()->GetPictureLayer();
}

void zedui::View::ReCreatePictureLayer() {
  picture_layer_ = zedbase::MakeRefCounted<PictureLayer>(
      GetLeft(), GetTop(), GetWidth(), GetHeight());
}

void View::Invalidate() {
  MarkDirty();
  if (auto parent = GetParent()) {
    parent->MarkDirty();
  }
}

bool View::IsDirty() const {
  return is_dirty_;
}

void View::MarkDirty() {
  is_dirty_ = true;
  for (const auto& child : children_) {
    child->MarkDirty();
  }
}

void View::BuildScene(SceneBuilder* scene_builder) {
  if (IsDirty()) {
    DrawContext draw_context(GetPictureLayer());
    OnDraw(draw_context);
    DrawCompleted();
  }

  for (auto child : children_) {
    child->BuildScene(scene_builder);
  }
}

void View::OnDraw(DrawContext& draw_context) {}

void View::DrawCompleted() {
  is_dirty_ = false;
}

std::unique_ptr<ViewTargeter> View::SetEventTargeter(
    std::unique_ptr<ViewTargeter> targeter) {
  std::unique_ptr<ViewTargeter> old_targeter = std::move(targeter_);
  targeter_ = std::move(targeter);
  return old_targeter;
}

ViewTargeter* View::GetEffectiveViewTargeter() const {
  ZED_DCHECK(GetWidget());
  ViewTargeter* view_targeter = targeter();
  if (!view_targeter) {
    view_targeter = GetWidget()->GetRootView()->targeter();
  }
  ZED_CHECK(view_targeter);
  return view_targeter;
}

bool View::CanAcceptEvent(const Event& event) {
  return IsVisible();
}

EventTarget* View::GetParentTarget() const {
  return parent_;
}

EventTargeter* View::GetEventTargeter() {
  return targeter_.get();
}

void View::AddChildViewAtImpl(View* view, size_t index) {
  ZED_CHECK((view != this)) << "Cannot add a view to itself.";
  View* parent = view->parent_;
  if (parent == this) {
    ReorderChildView(view, index);
    return;
  }

  view->parent_ = this;
  const auto pos = children_.insert(
      std::next(children_.cbegin(), static_cast<ptrdiff_t>(index)), view);

  YGNodeInsertChild(node_, view->node_, index);

  Invalidate();
}

void View::ReorderChildView(View* view, size_t index) {
  ZED_DCHECK(view->parent_ != this);
  const auto i = std::ranges::find(children_, view);
  ZED_DCHECK(i != children_.end());

  auto available_index = std::min(index, children_.size() - 1);
  const auto pos =
      std::next(children_.begin(), static_cast<ptrdiff_t>(available_index));
  if (i == pos) {
    return;
  }

  if (pos < i) {
    std::rotate(pos, i, std::next(i));
  } else {
    std::rotate(i, std::next(i), std::next(pos));
  }

  YGNodeRemoveChild(node_, view->node_);
  YGNodeInsertChild(node_, view->node_, available_index);

  Invalidate();
}

void View::DoRemoveChildView(View* view,
                             bool delete_removed_view,
                             View* new_parent) {
  ZED_CHECK(view);

  const auto i = FindChild(view);
  if (i == children_.cend()) {
    return;
  }

  std::unique_ptr<View> view_to_deleted;

  view->parent_ = nullptr;
  if (delete_removed_view) {
    view_to_deleted.reset(view);
  }
  children_.erase(i);
  YGNodeRemoveChild(node_, view->node_);
  Invalidate();
}

View::Views::const_iterator View::FindChild(const View* view) const {
  return std::ranges::find(children_, view);
}

}  // namespace zedui