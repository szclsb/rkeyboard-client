#include <rkb/Client.h>
#include <iostream>
#include <conio.h>

using namespace std;

int main() {
    auto client = rkb::Client("ws://localhost:3000", "");
    client.connect();
    bool terminate = false;
    char chr[1];

    printf("Press keys to send\n");
    while (!terminate) {
        //
        char c = _getch();
        if (c == '\n') {
            terminate = true;
        } else {
            client.send(string(1, c));
        }
    }

    client.disconnect();
    return 0;
}
