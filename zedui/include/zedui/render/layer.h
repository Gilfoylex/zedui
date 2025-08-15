#pragma once

#include "zedbase/memory/weak_ptr.h"
#include "zedbase/memory/ref_ptr.h"

namespace zedui {

class Renderer;
class Layer : public zedbase::RefCountedThreadSafe<Layer> {
 public:
  virtual ~Layer() = default;
  virtual void RenderToScreen(zedbase::WeakPtr<Renderer> renderer) = 0;

  ZED_FRIEND_MAKE_REF_COUNTED(Layer);
  ZED_FRIEND_REF_COUNTED_THREAD_SAFE(Layer);
};

}  // namespace zedui