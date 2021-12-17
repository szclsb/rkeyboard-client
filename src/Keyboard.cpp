#include <rkb/Keyboard.h>

#include <utility>
#include <winuser.rh>
#include <iostream>

using namespace std;

static rkb::Keyboard::f_key Callback;

static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (lParam != NULL)
    {
        auto kCode = ((LPKBDLLHOOKSTRUCT)lParam)->vkCode;
        if (wParam == WM_KEYDOWN) {
            if (kCode == VK_ESCAPE) {
                // ESC
                PostQuitMessage(0);
            } else {
                Callback(kCode, rkb::Keyboard::State::Down);
            }
        }
    }
    return CallNextHookEx(nullptr, nCode, wParam, lParam);
}

void rkb::Keyboard::detect(f_key callback) {
    Callback = std::move(callback);
    auto hook = SetWindowsHookExW(WH_KEYBOARD_LL, LowLevelKeyboardProc, nullptr, 0);
    MSG msg;
    while(GetMessage(&msg, nullptr, 0, 0)) {

    }
    UnhookWindowsHookEx(hook);
}

void rkb::Keyboard::press_key(int64_t key) {
    INPUT inputs[2] = {};
    ZeroMemory(inputs, sizeof(inputs));
    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = key;
    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = key;
    inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
}
