// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ZEDUI_GEOMETRY_QUATERNION_H_
#define ZEDUI_GEOMETRY_QUATERNION_H_

#include <ostream>

#include "zedui/geometry/vector.h"

namespace zedui {

struct Quaternion {
  union {
    struct {
      Scalar x;
      Scalar y;
      Scalar z;
      Scalar w;
    };
    Scalar e[4];
  };

  Quaternion() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}

  Quaternion(Scalar px, Scalar py, Scalar pz, Scalar pw)
      : x(px), y(py), z(pz), w(pw) {}

  Quaternion(const Vector3& axis, Scalar angle) {
    const auto sine = sin(angle * 0.5f);
    x = sine * axis.x;
    y = sine * axis.y;
    z = sine * axis.z;
    w = cos(angle * 0.5f);
  }

  Scalar Dot(const Quaternion& q) const {
    return x * q.x + y * q.y + z * q.z + w * q.w;
  }

  Scalar Length() const { return sqrt(x * x + y * y + z * z + w * w); }

  Quaternion Normalize() const {
    auto m = 1.0f / Length();
    return {x * m, y * m, z * m, w * m};
  }

  Quaternion Invert() const { return {-x, -y, -z, w}; }

  Quaternion Slerp(const Quaternion& to, double time) const;

  Quaternion operator*(const Quaternion& o) const {
    return {
        w * o.x + x * o.w + y * o.z - z * o.y,
        w * o.y + y * o.w + z * o.x - x * o.z,
        w * o.z + z * o.w + x * o.y - y * o.x,
        w * o.w - x * o.x - y * o.y - z * o.z,
    };
  }

  Quaternion operator*(Scalar scale) const {
    return {scale * x, scale * y, scale * z, scale * w};
  }

  Vector3 operator*(Vector3 vector) const {
    Vector3 v(x, y, z);
    return v * v.Dot(vector) * 2 +        //
           vector * (w * w - v.Dot(v)) +  //
           v.Cross(vector) * 2 * w;
  }

  Quaternion operator+(const Quaternion& o) const {
    return {x + o.x, y + o.y, z + o.z, w + o.w};
  }

  Quaternion operator-(const Quaternion& o) const {
    return {x - o.x, y - o.y, z - o.z, w - o.w};
  }

  bool operator==(const Quaternion& o) const {
    return x == o.x && y == o.y && z == o.z && w == o.w;
  }

  bool operator!=(const Quaternion& o) const {
    return x != o.x || y != o.y || z != o.z || w != o.w;
  }
};

}  // namespace zedui

namespace std {

inline std::ostream& operator<<(std::ostream& out, const zedui::Quaternion& q) {
  out << "(" << q.x << ", " << q.y << ", " << q.z << ", " << q.w << ")";
  return out;
}

}  // namespace std

#endif  // ZEDUI_GEOMETRY_QUATERNION_H_
