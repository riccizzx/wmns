
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


    printf("\nserver is listening for incomming connections...\n");
	printf("waiting for clients to connect...\n\n");

    try{

		// accept client connection
        if (listener.accept_client()) {

            char host[NI_MAXHOST];
            char serv[NI_MAXSERV];


            listener.get_client_info(host, serv);

            printf("client successfully connected!\n");

        }

    }catch(const std::exception& e){
        
        printf("server start error: %s\n", e.what());
        return false;
	
    }

    return true;

}

