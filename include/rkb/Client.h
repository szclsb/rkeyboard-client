#pragma once

#include <string>
#include <mutex>
#include <condition_variable>
#include <sio/sio_client.h>

namespace rkb {
    typedef std::function<void(int64_t)> f_msg;

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
        void send(int64_t c);
        void onMessage(const f_msg& callback);
    };
}
