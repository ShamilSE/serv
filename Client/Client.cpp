#include "Client.hpp"

void Client::log() {
	char client_ipv4_str[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &addr.sin_addr, client_ipv4_str, INET_ADDRSTRLEN);
	
	std::cout << "incoming connection from " << client_ipv4_str << ":" << addr.sin_port << std::endl;
}

void Client::initClient() {
	bzero(&addr, sizeof addr);
	request = nullptr;
	fd = 0;
}

Client::Client() {
	initClient();
}