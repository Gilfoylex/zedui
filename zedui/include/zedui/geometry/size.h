#pragma once

#include <tuple>

#include "zedui/geometry/float.h"
#include "zedui/geometry/point.h"
#include "zedui/utils/hash_combine.h"

namespace zedui {
/*
 * Contains width and height values.
 */
struct Size {
  Float width{0};
  Float height{0};

  Size& operator+=(const Point& point) noexcept {
    width += point.x;
    height += point.y;
    return *this;
  }

  Size& operator*=(const Point& point) noexcept {
    width *= point.x;
    height *= point.y;
    return *this;
  }

  static Size MakeWH(Float width, Float height) noexcept {
    return {width, height};
  }

  static Size Infinite() noexcept {
    return {std::numeric_limits<Float>::max(),
            std::numeric_limits<Float>::max()};
  }
};

inline bool operator==(const Size& rhs, const Size& lhs) noexcept {
  return std::tie(lhs.width, lhs.height) == std::tie(rhs.width, rhs.height);
}

inline bool operator!=(const Size& rhs, const Size& lhs) noexcept {
  return !(lhs == rhs);
}
}  // namespace zedui

namespace std {

template <>
struct hash<zedui::Size> {
  size_t operator()(const zedui::Size& size) const {
    return zedui::HashCombine(size.width, size.height);
  }
};

}  // namespace std