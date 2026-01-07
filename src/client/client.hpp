
#ifndef				CLIENT_CLIENT_HPP
#define 			CLIENT_CLIENT_HPP

#include "../common/config/config.hpp"
#include "../common/net/socket.hpp"

class Client{

private:
	net::TcpSocket client_socket;

public:

	bool create_socket();

	bool connect_to_server(const std::string& host, uint16_t port);

}

#endif