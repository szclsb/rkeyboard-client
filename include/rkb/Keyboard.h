#pragma once

#include "common.h"
#include <Windows.h>
#include <map>
#include <set>

namespace rkb {
    class Keyboard {
    private:
        static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

        std::set<int64_t> _pressed;
        std::map<std::string, KeyListener> _keyDownListeners;
        std::map<std::string, KeyListener> _keyUpListeners;
    public:
        static void scan(const std::shared_ptr<Keyboard>& keyboard);
        static void send(const KeyState& state, int64_t key);

        bool isPressed(int64_t key);
        void addKeyListener(const KeyState& state, const std::string& name, const KeyListener& callback);
        void removeKeyListener(const KeyState& state, const std::string& name);
    };

}
