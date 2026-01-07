
#include "socket.hpp"

#include <cstdio>

void net::TcpSocket::get_client_info(char* host, char* serv) {
    // Placeholder for getting client information

    host[NI_MAXHOST];
    serv[NI_MAXSERV];

	memset(host, 0, NI_MAXHOST);
	memset(serv, 0, NI_MAXSERV);
    
    try {
        if (getnameinfo((sockaddr*)&server_addr, sizeof(server_addr), host, NI_MAXHOST, serv, NI_MAXSERV, 0) == 0) {

			printf("client connected: %s:%s\n", host, serv);

        }
        else {

			inet_ntop(AF_INET, &server_addr.sin_addr, host, NI_MAXHOST);

            printf("client connected: %s:%d\n", host, ntohs(server_addr.sin_port));

        }

    }

    catch (const std::exception& e) {
        
        printf("get client info error: %s\n", e.what());
    
    }

}

bool net::TcpSocket::startapi() {

    if (WSAStartup(MAKEWORD(2, 2), &ws) != 0) {
        return false;
    }

	return true;

}

bool net::TcpSocket::create() {

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {

        return false;

    }

    return sock;

}

bool net::TcpSocket::bind(uint16_t port) {

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	return ::bind(sock, (sockaddr*)&server_addr, sizeof(server_addr)) != INVALID_SOCKET;

}

bool net::TcpSocket::listen(int backlog) {

    return ::listen(sock, backlog) == 0;

}

int net::TcpSocket::recv_bytes(void* buf, size_t len) {

    return ::recv(sock, static_cast<char*>(buf), len, 0);

}

int net::TcpSocket::send_bytes(const void* buf, size_t len) {

    return ::send(sock, static_cast<const char*>(buf), len, 0);

}

SOCKET net::TcpSocket::native() const {

    return sock;

}

int net::TcpSocket::accept_client() {
   
    int client_len = sizeof(client_addr);

    client_sock = accept(sock, (sockaddr*)&client_addr, &client_len);

    return client_sock;

}

int close(SOCKET s){

    if (s != INVALID_SOCKET) {

        s == INVALID_SOCKET;
	
        closesocket(s);
        WSACleanup();
        //EXIT_FAILURE;
    
    }

    return 0;

}