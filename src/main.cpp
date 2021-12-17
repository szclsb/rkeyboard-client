#include <rkb/Client.h>
#include <rkb/Keyboard.h>
#include <iostream>

using namespace std;

int WINAPI main(int argc, char *argv[]) {
    if (argc == 1) {
        return -1;
    }
    auto keyboard = make_shared<rkb::Keyboard>();
    auto client = rkb::Client("ws://localhost:3000", "");
    auto mode = string(argv[1]);
    if (mode == "send") {
        keyboard->addKeyListener(rkb::DOWN, "keyDown", [&client](const auto key) {
            client.send(rkb::DOWN, key);
        });
        keyboard->addKeyListener(rkb::UP, "keyUp", [&client](const auto key) {
            client.send(rkb::UP, key);
        });
        client.connect();
        rkb::Keyboard::scan(keyboard);
        client.disconnect();
    } else if (mode == "receive") {
        client.onMessage([](const auto state, const auto key) {
            rkb::Keyboard::send(state, key);
        });
        client.connect();
        rkb::Keyboard::scan(keyboard);
        client.disconnect();
    } else {
        return -1;
    }

    return 0;
}
