#pragma once

#include <Windows.h>

namespace rkb {
    class Keyboard {
    private:
        HHOOK _hook;
    public:
        Keyboard();
        ~Keyboard();
        void configure();
        void press_key();
    };
}
