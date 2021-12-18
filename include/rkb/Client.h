#pragma once

#include "common.h"
#include <string>
#include <mutex>
#include <condition_variable>
#include <sio_client.h>

namespace rkb {
    class Client {
    private:
        Client(auto &uri, auto &token);

        sio::client _client;
        std::mutex _mtx;
        std::condition_variable_any _cond;
        std::string _uri;
        std::string _token;
    public:
        explicit Client(std::string  uri, std::string  token);
        void connect();
        void disconnect();
        void send(const std::string& event, int64_t key);
        void onMessage(const std::string& event, const KeyListener& listener);
    };
}
