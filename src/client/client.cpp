
#include "client.hpp"

bool Client::create_socket() {
	return client_socket.create();
}

bool Client::connect_to_server(const std::string& host, uint16_t port) {

	sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	inet_pton(AF_INET, host.c_str(), &server_addr.sin_addr);
	
	if (connect(client_socket.native(), (sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
		return false;
	}

	return true;

}