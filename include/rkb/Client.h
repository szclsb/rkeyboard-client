#pragma once

#include <string>
#include <mutex>
#include <condition_variable>
#include <sio/sio_client.h>

namespace rkb {
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
        void send(std::string c);
    };
}
