#pragma once

#include <functional>

namespace rkb {
    typedef std::function<void(int64_t)> KeyListener;

    enum KeyState {
        DOWN,
        UP
    };
}
