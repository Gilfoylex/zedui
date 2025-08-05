#include "zedui/render/container_layer.h"
#include "zedui/render/draw_context.h"
#include "zedui/views/container_view.h"

namespace zedui {
ContainerView::ContainerView() : View() {}
ContainerView::~ContainerView() {}

void ContainerView::NotifyParentForRedraw() {
  if (auto parent = GetParent()) {
    parent->Invalidate();
  }
}

void ContainerView::Invalidate() {
  MarkDirty();
  NotifyParentForRedraw();
}

void ContainerView::MarkDirty() {
  is_dirty_ = true;
  for (const auto& child : children_) {
    child->MarkDirty();
  }
}

void ContainerView::Build(std::shared_ptr<ContainerLayer> layer_tree) {
  auto container_layer = std::make_shared<zedui::ContainerLayer>();
  layer_tree->Add(container_layer);
  auto picture_layer = GetPictureLayer();
  if (picture_layer) {
    container_layer->Add(picture_layer);
  }
  if (IsDirty()) {
    auto draw_context = DrawContext(GetLeft(), GetTop(), picture_layer);
    Draw(draw_context);
  }
  for (const auto& child : children_) {
    child->Build(container_layer);
  }
}

void ContainerView::AddChildViewAtImpl(View* view, size_t index) {
  ZED_CHECK((view != this)) << "Cannot add a view to itself.";
  ContainerView* parent = view->parent_;
  if (parent == this) {
    ReorderChildView(view, index);
    return;
  }

  view->parent_ = this;
  const auto pos = children_.insert(
      std::next(children_.cbegin(), static_cast<ptrdiff_t>(index)), view);

  Invalidate();
}

void ContainerView::ReorderChildView(View* view, size_t index) {
  ZED_DCHECK(view->parent_ != this);
  const auto i = std::ranges::find(children_, view);
  ZED_DCHECK(i != children_.end());

  const auto pos =
      std::next(children_.begin(),
                static_cast<ptrdiff_t>(std::min(index, children_.size() - 1)));
  if (i == pos) {
    return;
  }

  if (pos < i) {
    std::rotate(pos, i, std::next(i));
  } else {
    std::rotate(i, std::next(i), std::next(pos));
  }

  Invalidate();
}

void ContainerView::DoRemoveChildView(View* view,
                                      bool delete_removed_view,
                                      ContainerView* new_parent) {
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
  Invalidate();
}

ContainerView::Views::const_iterator ContainerView::FindChild(
    const View* view) const {
  return std::ranges::find(children_, view);
}
}  // namespace zedui