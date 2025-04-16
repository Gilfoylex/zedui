// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ZEDUI_GEOMETRY_SCALAR_H_
#define ZEDUI_GEOMETRY_SCALAR_H_

#include <cfloat>
#include <type_traits>
#include <valarray>

#include "zedui/geometry/constants.h"

namespace zedui {

// NOLINTBEGIN(google-explicit-constructor)

using Scalar = float;

template <class T, class = std::enable_if_t<std::is_arithmetic_v<T>>>
constexpr T Absolute(const T& val) {
  return val >= T{} ? val : -val;
}

template <>
constexpr Scalar Absolute<Scalar>(const float& val) {
  return fabsf(val);
}

constexpr inline bool ScalarNearlyZero(Scalar x,
                                       Scalar tolerance = kEhCloseEnough) {
  return Absolute(x) <= tolerance;
}

constexpr inline bool ScalarNearlyEqual(Scalar x,
                                        Scalar y,
                                        Scalar tolerance = kEhCloseEnough) {
  return ScalarNearlyZero(x - y, tolerance);
}

struct Degrees;

struct Radians {
  Scalar radians = 0.0;

  constexpr Radians() = default;

  explicit constexpr Radians(Scalar p_radians) : radians(p_radians) {}
};

struct Degrees {
  Scalar degrees = 0.0;

  constexpr Degrees() = default;

  explicit constexpr Degrees(Scalar p_degrees) : degrees(p_degrees) {}

  constexpr operator Radians() const {
    return Radians{degrees * kPi / 180.0f};
  };
};

// NOLINTEND(google-explicit-constructor)

}  // namespace zedui

#endif  // ZEDUI_GEOMETRY_SCALAR_H_
