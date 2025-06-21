#pragma once

#include "zedui/geometry/float.h"
#include "zedui/utils/hash_combine.h"

namespace zedui {
/*
 * Contains a point in a two-dimensional coordinate system.
 */
struct Point {
  Float x{0};
  Float y{0};

  inline Point& operator+=(const Point& point) noexcept {
    x += point.x;
    y += point.y;
    return *this;
  }

  inline Point& operator-=(const Point& point) noexcept {
    x -= point.x;
    y -= point.y;
    return *this;
  }

  inline Point& operator*=(const Point& point) noexcept {
    x *= point.x;
    y *= point.y;
    return *this;
  }

  inline Point operator+(const Point& rhs) const noexcept {
    return {
        .x = this->x + rhs.x,
        .y = this->y + rhs.y,
    };
  }
  inline Point operator-(const Point& rhs) const noexcept {
    return {
        .x = this->x - rhs.x,
        .y = this->y - rhs.y,
    };
  }

  inline Point operator-() const noexcept {
    return {
        .x = -x,
        .y = -y,
    };
  }

  static Point MakeXY(Float x, Float y) noexcept { return {x, y}; }
  static Point Round(Point other) noexcept {
    return {std::round(other.x), std::round(other.y)};
  }

  inline bool operator==(const Point& rhs) const = default;

  inline bool operator!=(const Point& rhs) const = default;
};
}  // namespace zedui

namespace std {

template <>
struct hash<zedui::Point> {
  inline size_t operator()(const zedui::Point& point) const noexcept {
    return zedui::HashCombine(point.x, point.y);
  }
};
}  // namespace std