#include "zedui/app.h"
#include "zedui/windows/window.h"

namespace zedui {
  
Window::Window() : Container(), in_redraw_(false) {
  Win32Window::Point origin(10, 10);
  Win32Window::Size size(width_, height_);
  auto ret = win32_window_.Create(L"ZedUI Window", origin, size);
}

Window::~Window() {}

void Window::Show() {
  win32_window_.Show();
}

void Window::OnCreated() {
  // create render target
}
void Window::OnDestroyed() {}
void Window::OnSizeChanged(int width, int height) {
  auto size =
      Size::MakeWH(static_cast<Float>(width), static_cast<Float>(height));
  SetSize(size);
}

void Window::NotifyParentForRedraw() {
  if (in_redraw_) {
    return;
  }
  in_redraw_ = true;
  App::Current->PostVsyncTask([this]() { DoFrame(); });
}

void Window::DrawCompleted() {
  Container::DrawCompleted();
}

void Window::SetWidth(float width) {
  const auto cast_width = static_cast<unsigned int>(width);
  if (width_ == cast_width) {
    return;
  }
  width_ = cast_width;
  Container::SetWidth(static_cast<float>(cast_width));
}

void Window::SetHeight(float height) {
  const auto cast_height = static_cast<unsigned int>(height);
  if (height_ == cast_height) {
    return;
  }
  height_ = cast_height;
  Container::SetHeight(static_cast<float>(cast_height));
}

void Window::SetSize(const Size& size) {
  const auto cast_width = static_cast<unsigned int>(size.width);
  const auto cast_height = static_cast<unsigned int>(size.height);
  if (width_ == cast_width && height_ == cast_height) {
    return;
  }
  width_ = cast_width;
  height_ = cast_height;
  Container::SetSize(Size::MakeWH(static_cast<float>(cast_width),
                                  static_cast<float>(cast_height)));
}

float Window::GetWidth() const {
  return static_cast<float>(width_);
}

float Window::GetHeight() const {
  return static_cast<float>(height_);
}

void Window::DoFrame() {
  in_redraw_ = false;

  // perform layout
  YGNodeCalculateLayout(node_, YGUndefined, YGUndefined, YGDirectionLTR);

  // build logic start
  auto container_layer = std::make_shared<zedui::ContainerLayer>();
  auto picture_layer = GetPictureLayer();
  if (picture_layer) {
    container_layer->Add(picture_layer);
  }
  if (IsDirty()) {
    auto draw_context = DrawContext(GetLeft(), GetTop(), picture_layer);
    Draw(draw_context);
  }
  for (const auto& child : childrens_) {
    child->Build(container_layer);
  }
  // build logic end

  // todo: post render task to render thread
}

void Window::Build(std::shared_ptr<ContainerLayer> layer_tree) {
  // window's build is done in DoFrame
}

void Window::Draw(DrawContext& draw_context){
  // todo 
}

}  // namespace zedui