#include <rkb/Client.h>
#include <rkb/Keyboard.h>
#include <iostream>

#define error_msg "invalid program arguments. Expected: send|receive <host> <port>"
#define keyDownEvent "keyDown"
#define keyUpEvent "keyUp"

using namespace std;

int WINAPI main(int argc, char *argv[]) {
    if (argc < 4) {
        cerr << error_msg;
        return -1;
    }
    auto mode = string(argv[1]);
    auto host = string(argv[2]);
    int port;
    sscanf_s(argv[3], "%d", &port);
    auto keyboard = make_shared<rkb::Keyboard>();
    stringstream ss;
    ss << "ws://" << host << ":" << port;
    auto client = rkb::Client(ss.str(), "");
    if (mode == "send") {
        keyboard->addKeyListener(rkb::DOWN, keyDownEvent, [&client](const auto key) {
            client.send(keyDownEvent, key);
        });
        keyboard->addKeyListener(rkb::UP, keyUpEvent, [&client](const auto key) {
            client.send(keyUpEvent, key);
        });
        client.connect();
        rkb::Keyboard::scan(keyboard);
        client.disconnect();
    } else if (mode == "receive") {
        client.onMessage(keyDownEvent, [](const auto key) {
            rkb::Keyboard::send(rkb::DOWN, key);
        });
        client.onMessage(keyUpEvent, [](const auto key) {
            rkb::Keyboard::send(rkb::UP, key);
        });
        client.connect();
        rkb::Keyboard::scan(keyboard);
        client.disconnect();
    } else {
        cerr << error_msg;
        return -1;
    }

    return 0;
}
