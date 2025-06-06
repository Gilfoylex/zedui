#ifndef ZEDUI_WINDOWS_WINDOW_DELEGATE_H_
#define ZEDUI_WINDOWS_WINDOW_DELEGATE_H_

namespace zedui {
class WindowDelegate{
    public:
    virtual void OnCreated() = 0;
    virtual void OnDestroyed() = 0;
    virtual void OnSizeChanged(int width, int height) = 0;
};
} // namespace zedui

#endif  // ZEDUI_WINDOWS_WINDOW_DELEGATE_H_