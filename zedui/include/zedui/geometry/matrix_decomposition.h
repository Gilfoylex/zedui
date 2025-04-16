// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ZEDUI_GEOMETRY_MATRIX_DECOMPOSITION_H_
#define ZEDUI_GEOMETRY_MATRIX_DECOMPOSITION_H_

#include "zedui/geometry/quaternion.h"
#include "zedui/geometry/scalar.h"
#include "zedui/geometry/shear.h"
#include "zedui/geometry/vector.h"


namespace zedui {

struct MatrixDecomposition {
  Vector3 translation;
  Vector3 scale;
  Shear shear;
  Vector4 perspective;
  Quaternion rotation;

  enum class Component {
    kTranslation = 1 << 0,
    kScale = 1 << 1,
    kShear = 1 << 2,
    kPerspective = 1 << 3,
    kRotation = 1 << 4,
  };

  uint64_t GetComponentsMask() const;
};

}  // namespace impeller

#endif  // ZEDUI_GEOMETRY_MATRIX_DECOMPOSITION_H_
