#ifndef ZEDUI_RENDER_DRAW_COMMAND_H_
#define ZEDUI_RENDER_DRAW_COMMAND_H_

namespace zedui {

enum class DrawType {
  None,
  Rect,
  Circle,
};

struct DrawCommand {
  DrawCommand() : type(DrawType::None) {}
  virtual ~DrawCommand() {}
  DrawType type;
};

struct DrawRectCommand final : public DrawCommand {
  DrawRectCommand() = delete;
  DrawRectCommand(float x, float y, float width, float height) {
    type = DrawType::Rect;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
  }
  float x;
  float y;
  float width;
  float height;
};

struct DrawCircleCommand final : public DrawCommand {
  DrawCircleCommand() = delete;
  DrawCircleCommand(float x, float y, float radius) {
    type = DrawType::Circle;
    this->x = x;
    this->y = y;
    this->radius = radius;
  }
  float x;
  float y;
  float radius;
};


}  // namespace zedui

#endif  // ZEDUI_RENDER_DRAW_COMMAND_H_