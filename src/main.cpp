#include <rkb/common.h>
#include <rkb/Client.h>
#include <rkb/Keyboard.h>
#include <iostream>

#define error_msg "invalid program arguments. Expected > send|receive <host> <port>"

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
    cout << "press LSHIFT + ESC to quit" << endl;
    stringstream ss;
    ss << "ws://" << host << ":" << port;
    auto client = rkb::Client(ss.str(), "");
    if (mode == mode_send) {
        keyboard->addKeyListener(rkb::DOWN, key_down_event, [&client](const auto key) {
            client.send(key_down_event, key);
        });
        keyboard->addKeyListener(rkb::UP, key_up_event, [&client](const auto key) {
            client.send(key_up_event, key);
        });
    } else if (mode == mode_receive) {
        client.onMessage(key_down_event, [](const auto key) {
            rkb::Keyboard::send(rkb::DOWN, key);
        });
        client.onMessage(key_up_event, [](const auto key) {
            rkb::Keyboard::send(rkb::UP, key);
        });
    } else {
        cerr << error_msg;
        return -1;
    }

    client.connect();
    cout << "ready to " << mode << " keystrokes " << (mode == mode_send ? "to" : "from") << " connected devices" << endl;
    rkb::Keyboard::scan(mode, keyboard);
    client.disconnect();

    return 0;
}
