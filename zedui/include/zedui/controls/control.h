#pragma once

namespace zedui {
class Control {

public:
    virtual ~Control() = default;
    virtual void Draw() = 0;

};
} // namespace zedui