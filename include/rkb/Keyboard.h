#pragma once

#include <Windows.h>
#include <functional>
#include <map>
#include <set>

namespace rkb {
    typedef std::function<void(int64_t)> KeyListener;

    class Keyboard {
    private:
        static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

        std::set<int64_t> _pressed;
        std::map<std::string, KeyListener> _keyDownListeners;
        std::map<std::string, KeyListener> _keyUpListeners;
    public:
        static void scan(const std::shared_ptr<Keyboard>& keyboard);
        static void press_key(int64_t key);

        bool isPressed(int64_t key);
        void addKeyDownListener(const std::string& name, const KeyListener& callback);
        void removeKeyDownListener(const std::string& name);
        void addKeyUpListener(const std::string& name, const KeyListener& callback);
        void removeKeyUpListener(const std::string& name);
    };

}
