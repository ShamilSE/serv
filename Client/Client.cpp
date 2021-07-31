#include "Client.hpp"

void Client::initClient() {
	bzero(&addr, sizeof addr);
	request = nullptr;
	fd = 0;
}

Client::Client() {
	initClient();
}

std::ostream& operator<<(std::ostream& out, const Client & client) {
	char client_ipv4_str[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &client.addr.sin_addr, client_ipv4_str, INET_ADDRSTRLEN);

	out << client_ipv4_str << ":" << client.addr.sin_port;

	return out;
}