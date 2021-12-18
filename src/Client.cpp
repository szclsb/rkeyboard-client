#include <rkb/Client.h>
#include <iostream>

using namespace std;

rkb::Client::Client(string uri, string token): _uri(move(uri)), _token(move(token)) {
    _client.set_open_listener([this]() {
        _mtx.lock();
        cout << "connected to " << _uri << endl;
        _cond.notify_all();
        _mtx.unlock();
    });
    _client.set_close_listener([this](sio::client::close_reason reason){
        cout << "disconnected from " << _uri << ", reason: " << reason << endl;
    });
    _client.set_fail_listener([this]() {
        cout << "error" << endl;
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

void rkb::Client::send(const string& event, int64_t key) {
    auto msg = sio::int_message::create(key);
    _client.socket()->emit(event, msg);
}

void rkb::Client::onMessage(const string& event, const KeyListener& listener) {
    _client.socket()->on(event, [listener](const sio::event &ev){
        const auto &msg = ev.get_message();
        const auto key = msg->get_int();
        listener(key);
    });
}