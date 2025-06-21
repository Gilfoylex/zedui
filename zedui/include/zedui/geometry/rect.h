#pragma once

#include <algorithm>
#include <tuple>

#include "zedui/geometry/float.h"
#include "zedui/geometry/point.h"
#include "zedui/geometry/size.h"
#include "zedui/utils/hash_combine.h"

namespace zedui {
/*
 * Contains the location and dimensions of a rectangle.
 */
struct Rect {
  Point origin{0, 0};
  Size size{0, 0};

  bool operator==(const Rect& rhs) const noexcept {
    return std::tie(this->origin, this->size) == std::tie(rhs.origin, rhs.size);
  }

  bool operator!=(const Rect& rhs) const noexcept { return !(*this == rhs); }

  Float GetMaxX() const noexcept {
    return size.width > 0 ? origin.x + size.width : origin.x;
  }
  Float GetMaxY() const noexcept {
    return size.height > 0 ? origin.y + size.height : origin.y;
  }
  Float GetMinX() const noexcept {
    return size.width >= 0 ? origin.x : origin.x + size.width;
  }
  Float GetMinY() const noexcept {
    return size.height >= 0 ? origin.y : origin.y + size.height;
  }
  Float GetMidX() const noexcept { return origin.x + size.width / 2; }
  Float GetMidY() const noexcept { return origin.y + size.height / 2; }
  Point GetCenter() const noexcept { return {GetMidX(), GetMidY()}; }

  void UnionInPlace(const Rect& rect) noexcept {
    auto x1 = std::min(GetMinX(), rect.GetMinX());
    auto y1 = std::min(GetMinY(), rect.GetMinY());
    auto x2 = std::max(GetMaxX(), rect.GetMaxX());
    auto y2 = std::max(GetMaxY(), rect.GetMaxY());
    origin = {x1, y1};
    size = {x2 - x1, y2 - y1};
  }

  bool ContainsPoint(Point point) noexcept {
    return point.x >= origin.x && point.y >= origin.y &&
           point.x <= (origin.x + size.width) &&
           point.y <= (origin.y + size.height);
  }

  static Rect MakeXYWH(Float x, Float y, Float width, Float height) noexcept {
    auto origin = Point::MakeXY(x, y);
    auto size = Size::MakeWH(width, height);
    return {origin, size};
  }

  static Rect MakeLTRB(Float left,
                       Float top,
                       Float right,
                       Float bottom) noexcept {
    auto origin = Point::MakeXY(left, top);
    auto size = Size::MakeWH(right - left, bottom - top);
    return {origin, size};
  }

  static Rect MakeOriginSize(Point origin, Size size) noexcept {
    return {origin, size};
  }

  static Rect Intersect(const Rect& rect1, const Rect& rect2) {
    Float x1 = std::max(rect1.origin.x, rect2.origin.x);
    Float y1 = std::max(rect1.origin.y, rect2.origin.y);
    Float x2 = std::min(rect1.origin.x + rect1.size.width,
                        rect2.origin.x + rect2.size.width);
    Float y2 = std::min(rect1.origin.y + rect1.size.height,
                        rect2.origin.y + rect2.size.height);

    Float intersectionWidth = x2 - x1;
    Float intersectionHeight = y2 - y1;

    if (intersectionWidth < 0 || intersectionHeight < 0) {
      return {};
    }

    return {{x1, y1}, {intersectionWidth, intersectionHeight}};
  }

  static Rect BoundingRect(const Point& a,
                           const Point& b,
                           const Point& c,
                           const Point& d) noexcept {
    auto leftTopPoint = a;
    auto rightBottomPoint = a;

    leftTopPoint.x = std::min(leftTopPoint.x, b.x);
    leftTopPoint.x = std::min(leftTopPoint.x, c.x);
    leftTopPoint.x = std::min(leftTopPoint.x, d.x);

    leftTopPoint.y = std::min(leftTopPoint.y, b.y);
    leftTopPoint.y = std::min(leftTopPoint.y, c.y);
    leftTopPoint.y = std::min(leftTopPoint.y, d.y);

    rightBottomPoint.x = std::max(rightBottomPoint.x, b.x);
    rightBottomPoint.x = std::max(rightBottomPoint.x, c.x);
    rightBottomPoint.x = std::max(rightBottomPoint.x, d.x);

    rightBottomPoint.y = std::max(rightBottomPoint.y, b.y);
    rightBottomPoint.y = std::max(rightBottomPoint.y, c.y);
    rightBottomPoint.y = std::max(rightBottomPoint.y, d.y);

    return {leftTopPoint,
            {rightBottomPoint.x - leftTopPoint.x,
             rightBottomPoint.y - leftTopPoint.y}};
  }
};

}  // namespace zedui

namespace std {

template <>
struct hash<zedui::Rect> {
  size_t operator()(const zedui::Rect& rect) const noexcept {
    return zedui::HashCombine(rect.origin, rect.size);
  }
};

}  // namespace std