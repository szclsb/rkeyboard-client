#pragma once

#include "State.h"
#include <string>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <sio_client.h>

namespace rkb {
    typedef std::function<void(State, int64_t)> f_msg;

    class Client {
    private:
        sio::client _client;
        std::mutex _mtx;
        std::condition_variable_any _cond;
        std::string _uri;
        std::string _token;
    public:
        explicit Client(std::string uri, std::string token);
        void connect();
        void disconnect();
        void send(const State& state, int64_t key);
        void onMessage(const f_msg& callback);
    };
}
