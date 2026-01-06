
#include "socket.hpp"

#include <cstdio>

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

net::TcpSocket net::TcpSocket::accept() {

    net::TcpSocket client;
    client.sock = ::accept(sock, nullptr, nullptr);
    return client;

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


int close(SOCKET s){

    if (s != INVALID_SOCKET) {

        s == INVALID_SOCKET;
	
        closesocket(s);
        WSACleanup();
        //EXIT_FAILURE;
    
    }

    return 0;

}