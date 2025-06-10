#include "zedui/controls/container.h"

namespace zedui {
Container::Container() : UIContainer() {}
Container::Container(std::shared_ptr<UIContainer> parent)
    : UIContainer(parent) {}
}