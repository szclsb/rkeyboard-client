#pragma once

#include <Windows.h>
#include <functional>

namespace rkb::Keyboard {
    enum State {
        UP,
        Down
    };

    typedef std::function<void(int64_t, State)> f_key;

    void detect(f_key callback);
    void press_key(int64_t key);
}
