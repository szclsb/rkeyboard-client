#include <rkb/Client.h>
#include <iostream>

using namespace std;

rkb::Client::Client(string uri, string token): _uri(move(uri)), _token(move(token)) {
    _client.set_open_listener([this]() {
        _mtx.lock();
        _cond.notify_all();
        _mtx.unlock();
    });
    _client.set_fail_listener([this]() {
        cout << "error" << endl;
    });
    _client.socket()->on("key", [this](const sio::event &ev){
        const auto &msg = ev.get_message();
        const auto c = msg->get_int();
        //FIXME
        cout << "received char: " << char(c) << endl;
    });
}

void rkb::Client::connect() {
    // connect to websocket
    // <uri>/socket.io/?EIO=4&t=<now>&transport=websocket <- will be set by client.
    // Do not change or override those queries to avoid invalid http status
    // https://github.com/socketio/socket.io-client-cpp/blob/master/src/internal/sio_client_impl.cpp
    _mtx.lock();
    _client.connect(_uri);
    _cond.wait(_mtx);
    _mtx.unlock();
//    _client.connect(_uri, {
//            {"token", _token}
//    });
}

void rkb::Client::disconnect() {
    _client.socket()->close();
}

void rkb::Client::send(string c) {
    _client.socket()->emit("key", c);
//    cout << "sending " << c << endl;
}
