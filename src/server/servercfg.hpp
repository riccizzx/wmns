
// server/server.hpp
#pragma once

#include "../common/config/config.hpp"
#include "../common/net/socket.hpp"

using namespace config;

namespace net {

    class server {

    public:

        bool start();
        void run();

    private:

        TcpSocket listener;
        TcpSocket client;

        void handle_connection();
        void normal_channel();

    };

}
