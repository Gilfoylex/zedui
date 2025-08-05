#pragma once
#include <memory>
#include <vector>
#include "zedbase/logging.h"
#include "zedbase/memory/ptr_util.h"
#include "zedbase/containers/contains.h"
#include "zedui/render/picture_layer.h"
#include "zedui/views/view.h"

namespace zedui {
class ContainerView : public View,
                      public std::enable_shared_from_this<ContainerView> {
 public:
  using Views = std::vector<View*>;
  ContainerView();
  virtual ~ContainerView();

  virtual void NotifyParentForRedraw();
  std::shared_ptr<PictureLayer> GetPictureLayer();
  // View overrides
  void Invalidate() override;
  void MarkDirty() override;
  void Build(std::shared_ptr<ContainerLayer> layer_tree) override;

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
                                 ContainerView* new_parent);

  Views::const_iterator FindChild(const View* view) const;

 protected:
  Views children_;
  std::shared_ptr<PictureLayer> picture_layer_;
};
}  // namespace zedui