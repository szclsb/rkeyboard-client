#include <rkb/Keyboard.h>

#include <utility>
#include <winuser.rh>
#include <iostream>
#include <algorithm>

using namespace std;

rkb::Keyboard __keyboard;

LRESULT CALLBACK rkb::Keyboard::LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0 && lParam != NULL) {
        auto key = ((LPKBDLLHOOKSTRUCT) lParam)->vkCode;
        // intercepts system key, so ALT+TAB and other system shortcuts won't work
        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            if (key == VK_ESCAPE && __keyboard._pressed.contains(VK_LSHIFT)) {
                PostQuitMessage(0);
            } else if (!__keyboard._pressed.contains(key)) {
                __keyboard._pressed.insert(key);
                for (const auto&[_, listener]: __keyboard._keyDownListeners) {
                    listener(key);
                }
            }
        } else if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP) {
            __keyboard._pressed.erase(key);
            for (const auto&[_, listener]: __keyboard._keyUpListeners) {
                listener(key);
            }
        }
        return LRESULT(1);
    }
    return CallNextHookEx(nullptr, nCode, wParam, lParam);
}

void rkb::Keyboard::scan(const shared_ptr<rkb::Keyboard> &keyboardPtr) {
    if (keyboardPtr == nullptr) {
        exit(-1);
    }
    __keyboard = *keyboardPtr;
    auto hook = SetWindowsHookExW(WH_KEYBOARD_LL, rkb::Keyboard::LowLevelKeyboardProc, nullptr, 0);
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {}
    UnhookWindowsHookEx(hook);
}

void rkb::Keyboard::send(const rkb::KeyState &state, int64_t key) {
    INPUT inputs[1] = {};
    ZeroMemory(inputs, sizeof(inputs));
    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = key;
    if (state == rkb::UP) {
        inputs[0].ki.dwFlags = KEYEVENTF_KEYUP;
    }
    SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
}

bool rkb::Keyboard::isPressed(const int64_t key) {
    return _pressed.contains(key);
}

void rkb::Keyboard::addKeyListener(const rkb::KeyState &state, const string &name, const rkb::KeyListener &callback) {
    if (state == DOWN) {
        _keyDownListeners.insert(pair<string, rkb::KeyListener>(name, callback));
    } else if (state == UP) {
        _keyUpListeners.insert(pair<string, rkb::KeyListener>(name, callback));
    }
}

void rkb::Keyboard::removeKeyListener(const rkb::KeyState &state, const string &name) {
    if (state == DOWN) {
        _keyDownListeners.erase(name);
    } else if (state == UP) {
        _keyUpListeners.erase(name);
    }
}
