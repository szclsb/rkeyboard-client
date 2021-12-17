#include <rkb/Keyboard.h>

#include <iostream>

using namespace std;

static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (lParam != NULL)
    {
        auto kCode = ((LPKBDLLHOOKSTRUCT)lParam)->vkCode;
        if (wParam == WM_KEYDOWN) {
            if (kCode == 27) {
                PostQuitMessage(0);
            }
            cout << kCode << endl;
        }
    }
    return CallNextHookEx(nullptr, nCode, wParam, lParam);
}

rkb::Keyboard::Keyboard() {
    _hook = SetWindowsHookExW(WH_KEYBOARD_LL, LowLevelKeyboardProc, nullptr, 0);
    MSG msg;
    while(GetMessage(&msg, nullptr, 0, 0)) {

    }
}

rkb::Keyboard::~Keyboard() {
    UnhookWindowsHookEx(_hook);
}

void rkb::Keyboard::press_key() {

}
