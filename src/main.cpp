//#include <rkb/Client.h>
#include <rkb/Keyboard.h>
#include <iostream>
#include <conio.h>

using namespace std;

int WINAPI main(int argc, char *argv[]) {
//    if (argc == 1) {
//        return -1;
//    }
//    auto mode = string(argv[1]);
//    if (mode == "send") {
//        auto client = rkb::Client("ws://localhost:3000", "");
//        client.connect();
//        bool terminate = false;
//        printf("Press keys to send\n");
//        while (!terminate) {
//            // read single character before enter, replace with keystroke WIN32
//            int c = _getch();
//            if (c == '\n') {
//                terminate = true;
//            } else {
//                client.send(c);
//            }
//        }
//        client.disconnect();
//    } else if (mode == "receive") {
//        auto client = rkb::Client("ws://localhost:3000", "");
//        client.onMessage([](const int64_t c) {
//            // todo simulate keystrokes
//            cout << c << endl;
//        });
//        client.connect();
//        cin.ignore();
//        client.disconnect();
//    } else {
//        return -1;
//    }

    auto keyboard = make_shared<rkb::Keyboard>();
    keyboard->addKeyDownListener("print", [](auto key) {
        cout << key << endl;
    });
    rkb::Keyboard::scan(keyboard);

//    rkb::press_key(91);

    return 0;
}
