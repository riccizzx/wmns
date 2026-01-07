
#include "servercfg.hpp"

bool net::server::start() {


    if (!listener.startapi()) {
        handle_error("WSAStartup failed");
        return false;
    }


    if (!listener.create()) {
        handle_error("socket creation failed");
        return false;
    }


    if (!listener.bind(DEFAULT_PORT)) {
        handle_error("bind failed");
        return false;
    }


    if (!listener.listen(SOMAXCONN)) {
        handle_error("listen failed");
        return false;
    }


    printf("Server listening on port %d\n", DEFAULT_PORT);
    return true;

}

