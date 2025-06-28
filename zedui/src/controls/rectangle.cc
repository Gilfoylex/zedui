#include "zedui\controls\rectangle.h"
#include "zedui\geometry\size.h"

namespace zedui {

  Rectangle::Rectangle(){
    SetFlexGrow(1);
  }

Rectangle::Rectangle(float width, float height) {
  SetSize(Size::MakeWH(width, height));
}

void Rectangle::Draw(DrawContext& draw_context) {
  auto left = GetLeft();
  auto top = GetTop();
  auto width = GetWidth();
  auto height = GetHeight();
  draw_context.DrawRectangle(left, top, width, height);
}

}  // namespace zedui