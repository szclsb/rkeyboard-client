#pragma once

#include <functional>

#define key_down_event "keyDown"
#define key_up_event "keyUp"
#define mode_send "send"
#define mode_receive "receive"

namespace rkb {
    typedef std::function<void(int64_t)> KeyListener;

    enum KeyState {
        DOWN,
        UP
    };
}
