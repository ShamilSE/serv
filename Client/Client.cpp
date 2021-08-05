#include "Client.hpp"

void Client::initClient() {
	// isWaitingForResponse = 0;
	bzero(&addr, sizeof addr);
	request = nullptr;
	response = nullptr;
	fd = 0;
}

Client::Client() {initClient();}

Client::~Client() {
	delete request;
	delete response;
}

std::ostream& operator<<(std::ostream& out, const Client & client) {
	char client_ipv4_str[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &client.addr.sin_addr, client_ipv4_str, INET_ADDRSTRLEN);

	out << client_ipv4_str << ":" << client.addr.sin_port;

	return out;
}

void Client::setRequest(Request* request) {this->request = request;}
void Client::setResponse(Response* response) {this->response = response;}
