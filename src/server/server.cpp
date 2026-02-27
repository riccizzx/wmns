
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


    if (listener.listen(SOMAXCONN) == SOCKET_ERROR) {
        handle_error("listen failed");
        return false;
    }
    else {
        std::cout << "server is in listening state!\n";
    }

    return true;
}

int net::server::handle_client_communication()
{
    while (true)   // accept loop
    {
        SOCKET client_sock = listener.accept_client();

        if (client_sock == INVALID_SOCKET)
            continue;

        std::cout << "Client connected!\n";

        char buffer[1024];

        while (true)  // client communication loop
        {
            memset(buffer, 0, sizeof(buffer));

            int bytes_recv = recv(client_sock, buffer, sizeof(buffer), 0);

            if (bytes_recv > 0)
            {
                std::string recv_msg(buffer, bytes_recv);
                std::cout << "Client: " << recv_msg << std::endl;

                if (recv_msg == "exit")
                    break;

                //int bytes_send = send(client_sock, buffer, sizeof(buffer), 0);
                send(client_sock, buffer, bytes_recv, 0);
            }
            else
            {
                break; // client disconnected or error
            }
        }

        closesocket(client_sock);
        std::cout << "Client disconnected.\n";
    }

    return 0;
}