#pragma once

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
  DrawRectCommand(float left, float top, float width, float height) {
    type = DrawType::Rect;
    this->left = left;
    this->top = top;
    this->right = left + width;
    this->bottom = top + height;
  }
  float left;
  float top;
  float right;
  float bottom;
};

struct DrawCircleCommand final : public DrawCommand {
  DrawCircleCommand() = delete;
  DrawCircleCommand(float left, float top, float radius) {
    type = DrawType::Circle;
    this->left = left;
    this->top = top;
    this->radius = radius;
  }
  float left;
  float top;
  float radius;
};


}  // namespace zedui