#include "Server.hpp"

Server::Server(std::string config) {
	_conf = new Configuration(config);
	_getServerAddr();

	_createSocket();
	_lstn(sock);
}

// Server::Server(const Server& other) {*this = other;}

// Server& Server::operator=(const Server& other) {

// }

Server::~Server() {}

void Server::_getServerAddr() {
	this->port = stoi(_conf->fields["port"]);
	bzero(&server_addr, sizeof server_addr);
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(0);
	server_addr.sin_port = htons(port);

	fcntl(sock, F_SETFL, O_NONBLOCK);
}

void Server::_lstn(int sock) {
	if (-1 == ::listen(sock, 3)) {
		perror("listen");
		exit(1);
	}
	std::cout << "server is listening for " << port << " port" << std::endl;
}

void Server::_createSocket() {
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		perror("sock");
		exit(1);
	}
	int opt = 1;
	if (-1 == setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
		perror("setsockopt");
		exit(1);
	}
	if (-1 == bind(sock, (struct sockaddr*)&server_addr, sizeof server_addr)) {
		perror("bind");
		exit(1);
	}
}

int Server::getSock() {return sock;}
Configuration* Server::getConfig() {return _conf;}
